/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppFileMagic - file(1) and libmagic(3) inspired plugin for Notepad++   //
//  Copyright (c) 2015 Frank Fesevur                                       //
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

#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "NPP/PluginInterface.h"
#include "Resource.h"
#include "NppFileMagic.h"
#include "DlgAbout.h"
#include "FileSettingsVim.h"

static const int nbFunc = 1;
static const TCHAR PLUGIN_NAME[] = L"FileMagic";

HINSTANCE g_hInst;
NppData g_nppData;
static FuncItem s_funcItem[nbFunc];

/////////////////////////////////////////////////////////////////////////////
//

static char* GetLine(int linenumber)
{
	// Get the number of lines
	int lines = SendMsg(SCI_GETLINECOUNT);
	if (linenumber > lines)
		return NULL;

	// Get the length of the requested line
	int len = SendMsg(SCI_LINELENGTH, linenumber);
	if (len == 0)
		return NULL;

	// Allocate enough space to store the line
	char* szLine = new char[len + 10];

	if (szLine != NULL)
	{
		// Clear the buffer
		ZeroMemory(szLine, len + 10);

		// Get the text of the requested line
		SendMsg(SCI_GETLINE, linenumber, (LPARAM) szLine);
	}
	return szLine;
}

/////////////////////////////////////////////////////////////////////////////
//

static void ParseFirstLine()
{
	// Get the first line of the file
	char* szText = GetLine(0);

	// Is that line filled?
	if (szText == NULL)
		return;

	// Does it contain a SheBang?
	if (strncmp(szText, "#!/", 3) == 0)
	{
		// Try as many languages as possible
		if (strstr(szText, "python") != NULL)
			SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_PYTHON);
		else if (strstr(szText, "perl") != NULL)
			SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_PERL);
		else if (strstr(szText, "php") != NULL)
			SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_PHP);
		else if (strstr(szText, "ruby") != NULL)
			SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_RUBY);
		else if (strstr(szText, "sh") != NULL)
			SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_BASH);
	}
	else if (strncmp(szText, "<?xml", 5) == 0)
	{
		SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_XML);
	}

	delete[] szText;
}

/////////////////////////////////////////////////////////////////////////////
// Search in the file for the various file settings for the various editors

static void SearchEditorFileSettings()
{
	int lines = SendMsg(SCI_GETLINECOUNT) - 1;
	if (lines <= 0)
		return;

	bool found = false;
	int fivesLinesAbove = (lines > 5 ? lines - 5 : 0);
	for (int i = lines; !found && i >= fivesLinesAbove; i--)
	{
		// Get the line of the file
		char* szLine = GetLine(i);
		if (szLine != NULL)
		{
			FileSettingsVim vim(szLine);
			if (vim.Parse())
				found = true;

			delete[] szLine;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	g_nppData = notpadPlusData;
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

HWND getCurrentHScintilla(int which)
{
	return (which == 0) ? g_nppData._scintillaMainHandle : g_nppData._scintillaSecondHandle;
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
			ParseFirstLine();
			SearchEditorFileSettings();
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
// Copy an Ansi string to a Unicode string

void Ansi2Unicode(LPWSTR wszStr, LPCSTR szStr, int iSize)
{
	if (szStr != NULL)
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, wszStr, iSize);
	else
		*wszStr = L'\0';
}

/////////////////////////////////////////////////////////////////////////////
// Easy access to the MessageBox functions

void MsgBox(const WCHAR* msg)
{
	::MessageBox(g_nppData._nppHandle, msg, PLUGIN_NAME, MB_OK);
}

void MsgBox(const char* msg)
{
	TCHAR* tmp = (TCHAR*) malloc(sizeof(TCHAR) * (strlen(msg) + 2));
	Ansi2Unicode(tmp, msg, (int) strlen(msg) + 1);
	::MessageBox(g_nppData._nppHandle, tmp, PLUGIN_NAME, MB_OK);
	free(tmp);
}

bool MsgBoxYesNo(const WCHAR* msg)
{
	return (MessageBox(g_nppData._nppHandle, msg, PLUGIN_NAME, MB_YESNO) == IDYES);
}

/////////////////////////////////////////////////////////////////////////////
// MessageBox function with printf

void MsgBoxf(const char* szFmt, ...)
{
	char szTmp[1024];
	va_list argp;
	va_start(argp, szFmt);
	vsprintf(szTmp, szFmt, argp);
	va_end(argp);
	MsgBox(szTmp);
}

/////////////////////////////////////////////////////////////////////////////
// Send a simple message to the Notepad++ window 'count' times and return
// the last result.

LRESULT SendMsg(UINT Msg, WPARAM wParam, LPARAM lParam, int count)
{
	int currentEdit;
	::SendMessage(g_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM) &currentEdit);
	LRESULT res = 0;
	for (int i = 0; i < count; i++)
		res = ::SendMessage(getCurrentHScintilla(currentEdit), Msg, wParam, lParam);
	return res;
}

/////////////////////////////////////////////////////////////////////////////
// Make the window center, relative the NPP-window

void CenterWindow(HWND hDlg)
{
	RECT rc;
	GetClientRect(g_nppData._nppHandle, &rc);

	POINT center;
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	center.x = rc.left + (w / 2);
	center.y = rc.top + (h / 2);
	ClientToScreen(g_nppData._nppHandle, &center);

	RECT dlgRect;
	GetClientRect(hDlg, &dlgRect);
	int x = center.x - ((dlgRect.right - dlgRect.left) / 2);
	int y = center.y - ((dlgRect.bottom - dlgRect.top) / 2);

	SetWindowPos(hDlg, HWND_TOP, x, y, -1, -1, SWP_NOSIZE | SWP_SHOWWINDOW);
}

/////////////////////////////////////////////////////////////////////////////
//

WCHAR* GetDlgText(HWND hDlg, UINT uID)
{
	int maxBufferSize = GetWindowTextLength(GetDlgItem(hDlg, uID)) + 3;
	WCHAR* buffer = new WCHAR[maxBufferSize];
	ZeroMemory(buffer, maxBufferSize);

	GetDlgItemText(hDlg, uID, buffer, maxBufferSize);
	return buffer;
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
			wcscpy(s_funcItem[index]._itemName, L"About...");
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
