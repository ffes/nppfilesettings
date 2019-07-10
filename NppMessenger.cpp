/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppFileSettings                                                        //
//  Copyright (c) 2015-2016 Frank Fesevur                                  //
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
#include "NppMessenger.h"

NppMessenger::NppMessenger(HWND hSciWnd)
{
	m_hSciWnd = hSciWnd;
	m_pSciMsg = (SciFnDirect) SendMessage(m_hSciWnd, SCI_GETDIRECTFUNCTION, 0, 0);
	m_pSciWndData = (sptr_t) SendMessage(m_hSciWnd, SCI_GETDIRECTPOINTER, 0, 0);
}

NppMessenger::~NppMessenger()
{
}

LRESULT NppMessenger::SendSciMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return m_pSciMsg(m_pSciWndData, uMsg, wParam, lParam);
}

LRESULT NppMessenger::SendSciMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) const
{
	return m_pSciMsg(m_pSciWndData, uMsg, wParam, lParam);
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
	//SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, lang);
}
