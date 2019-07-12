/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppMessenger v1.0.0                                                    //
//  Copyright (c) 2019 Frank Fesevur                                       //
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

#include "NppMessenger.h"

NppMessenger::NppMessenger()
{
}

NppMessenger::NppMessenger(NppData notpadPlusData)
{
	SetNppData(notpadPlusData);
}

NppMessenger::~NppMessenger()
{
}

void NppMessenger::SetNppData(NppData notpadPlusData)
{
	m_nppData = notpadPlusData;
}

LRESULT NppMessenger::SendNppMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendMessage(m_nppData._nppHandle, uMsg, wParam, lParam);
}

LRESULT NppMessenger::SendNppMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) const
{
	return SendMessage(m_nppData._nppHandle, uMsg, wParam, lParam);
}

LRESULT NppMessenger::SendSciMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int currentEdit = 0;
	SendMessage(m_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentEdit);

	HWND hWndScintilla = (currentEdit == 0) ? m_nppData._scintillaMainHandle : m_nppData._scintillaSecondHandle;
	return SendMessage(hWndScintilla, uMsg, wParam, lParam);
}

LRESULT NppMessenger::SendSciMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) const
{
	int currentEdit = 0;
	SendMessage(m_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentEdit);

	HWND hWndScintilla = (currentEdit == 0) ? m_nppData._scintillaMainHandle : m_nppData._scintillaSecondHandle;
	return SendMessage(hWndScintilla, uMsg, wParam, lParam);
}

int NppMessenger::GetLineCount() const
{
	return (int) SendSciMsg(SCI_GETLINECOUNT);
}

int NppMessenger::GetLineLength(int line) const
{
	return (int) SendSciMsg(SCI_LINELENGTH, (WPARAM) line);
}

int NppMessenger::GetLine(int line, char* textbuf) const
{
	return (int) SendSciMsg(SCI_GETLINE, (WPARAM) line, (LPARAM) textbuf);
}

void NppMessenger::SetTabWidth(int width) const
{
	SendSciMsg(SCI_SETTABWIDTH, width);
}

void NppMessenger::SetUseTabs(bool usetabs) const
{
	SendSciMsg(SCI_SETUSETABS, usetabs ? 1 : 0);
}

void NppMessenger::SetLanguage(LangType lang) const
{
	SendNppMsg(NPPM_SETCURRENTLANGTYPE, 0, lang);
}
