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

#pragma once

#include "NPP/PluginInterface.h"

class NppMessenger
{
public:
	NppMessenger();
	NppMessenger(NppData notpadPlusData);
	virtual ~NppMessenger();

	void SetNppData(NppData notpadPlusData);
	HWND GetNppHandle() const { return m_nppData._nppHandle; };

	LRESULT SendNppMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0);
	LRESULT SendNppMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;

	LRESULT	SendSciMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0);
	LRESULT SendSciMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;

	int			GetLineCount() const;
	int			GetLineLength(int line) const;
	int			GetLine(int line, char* textbuf) const;

	void		SetTabWidth(int width) const;
	void		SetUseTabs(bool usetabs) const;
	void		SetLanguage(LangType lang) const;

protected:
	NppData m_nppData;
};
