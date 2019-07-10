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

#pragma once

#include "NPP/PluginInterface.h"

class NppMessenger
{
public:
	NppMessenger(HWND hSciWnd = nullptr);
	virtual ~NppMessenger();

	//LRESULT SendNppMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;
	LRESULT	SendSciMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0);
	LRESULT SendSciMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;

	HWND		GetSciWnd() const  { return m_hSciWnd; }
	void		SetSciWnd(HWND hSciWnd)  { m_hSciWnd = hSciWnd; }

	int			GetLineCount() const;
	int			GetLineLength(int line) const;
	int			GetLine(int line, char* textbuf) const;

	void		SetTabWidth(int width) const;
	void		SetUseTabs(bool usetabs) const;
	void		SetLanguage(LangType lang) const;

protected:
	HWND m_hSciWnd;
	SciFnDirect m_pSciMsg;
	sptr_t m_pSciWndData;
};
