/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppFileSettings                                                        //
//  Copyright (c) 2015-2022 Frank Fesevur                                  //
//                                                                         //
//  This program is free software; you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by   //
//  the Free Software Foundation; either version 2 of the License, or      //
//  (at your option) any later version.                                    //
//                                                                         //
//  This program is distributed in the hope that it will be useful,        //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           //
//  GNU General Public License for more details.                           //
//                                                                         //
//  You should have received a copy of the GNU General Public License      //
//  along with this program; if not, write to the Free Software            //
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <assert.h>

#include "NPP/PluginInterface.h"
#include "Resource.h"
#include "NppFileSettings.h"
#include "DlgAbout.h"
#include "FileSettingsVim.h"
#include "NppMessenger.h"

static const int nbFunc = 1;
static const TCHAR PLUGIN_NAME[] = L"FileSettings";

HINSTANCE g_hInst;
NppMessenger g_Msgr;
static FuncItem s_funcItem[nbFunc];

/////////////////////////////////////////////////////////////////////////////
//

static std::string GetLine(int linenumber)
{
	// Get the number of lines
	const int lines = g_Msgr.GetLineCount();
	if (linenumber > lines)
		return "";

	// Get the length of the requested line
	const int len = g_Msgr.GetLineLength(linenumber);
	if (len == 0)
		return "";

	// Allocate enough space to store the line
	char* szLine = new char[len + 10];
	if (szLine != nullptr)
	{
		// Clear the buffer
		ZeroMemory(szLine, len + 10);

		// Get the text of the requested line
		g_Msgr.GetLine(linenumber, szLine);
	}

	std::string ret = szLine;
	delete[] szLine;

	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// Search in the file for the various file settings for the various editors

static void SearchForFileSettings(int linesToSearch)
{
	// Get the total number of lines in the file
	const int totalLines = g_Msgr.GetLineCount() - 1;
	if (totalLines <= 0)
		return;

	// Search the bottom `linesToSearch` lines
	const int linesAtBottom = (totalLines > linesToSearch ? totalLines - linesToSearch : 0);
	for (int i = totalLines; i >= linesAtBottom; i--)
	{
		// Get the line of the file
		std::string line = GetLine(i);
		if (line.length() > 0)
		{
			FileSettingsVim vim(&g_Msgr, line);
			if (vim.Parse())
				return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	g_Msgr.SetNppData(notpadPlusData);
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) const TCHAR* getName()
{
	return PLUGIN_NAME;
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) FuncItem* getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return s_funcItem;
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) void beNotified(SCNotification* notifyCode)
{
	switch (notifyCode->nmhdr.code)
	{
		case NPPN_READY:
		{
			break;
		}

		case NPPN_SHUTDOWN:
		{
			break;
		}

		case NPPN_BUFFERACTIVATED:
		{
			// TODO: Make number of line to search for configurable
			SearchForFileSettings(5);	// Search 5 lines
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Here you can process the Npp Messages
// I will make the messages accessible little by little, according to the
// need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781

extern "C" __declspec(dllexport) LRESULT messageProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(uMsg);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Easy access to the MessageBox function

void MsgBox(const std::string msg)
{
	std::wstring tmp(msg.begin(), msg.end());
	MessageBox(g_Msgr.GetNppHandle(), tmp.c_str(), PLUGIN_NAME, MB_OK);
}

/////////////////////////////////////////////////////////////////////////////
// Make the window center, relative to the NPP-window

void CenterWindow(HWND hDlg) noexcept
{
	RECT rc;
	GetClientRect(g_Msgr.GetNppHandle(), &rc);
	const int w = rc.right - rc.left;
	const int h = rc.bottom - rc.top;

	POINT center;
	center.x = rc.left + (w / 2);
	center.y = rc.top + (h / 2);
	ClientToScreen(g_Msgr.GetNppHandle(), &center);

	RECT dlgRect;
	GetClientRect(hDlg, &dlgRect);
	const int x = center.x - ((dlgRect.right - dlgRect.left) / 2);
	const int y = center.y - ((dlgRect.bottom - dlgRect.top) / 2);

	SetWindowPos(hDlg, HWND_TOP, x, y, -1, -1, SWP_NOSIZE | SWP_SHOWWINDOW);
}

/////////////////////////////////////////////////////////////////////////////
// The entry point of the DLL

BOOL APIENTRY DllMain(HANDLE hModule, DWORD reasonForCall, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (reasonForCall)
	{
		case DLL_PROCESS_ATTACH:
		{
			g_hInst = (HINSTANCE) hModule;

			// The most important menu entry
			int index = 0;
/*
			s_funcItem[index]._pFunc = NULL;
			wcscpy(s_funcItem[index]._itemName, PLUGIN_NAME);
			s_funcItem[index]._init2Check = false;
			s_funcItem[index]._pShKey = NULL;
			index++;

			// Seperator
			s_funcItem[index]._pFunc = NULL;
			wcscpy(s_funcItem[index]._itemName, L"-SEPARATOR-");
			s_funcItem[index]._init2Check = false;
			s_funcItem[index]._pShKey = NULL;
			index++;
*/
			// Show About Dialog
			s_funcItem[index]._pFunc = ShowAboutDlg;
			wcscpy_s(s_funcItem[index]._itemName, L"About...");
			s_funcItem[index]._init2Check = false;
			s_funcItem[index]._pShKey = NULL;
			index++;
			assert(index == nbFunc);
			break;
		}

		case DLL_PROCESS_DETACH:
		{
/*
			// Don't forget to deallocate your shortcut here
			delete g_funcItem[0]._pShKey;

			// Delete the toolbar
			DeleteObject(hbmpToolbar);

			// Clean up the options
			delete g_Options;
*/
			break;
		}

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
