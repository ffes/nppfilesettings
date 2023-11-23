/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppFileSettings                                                        //
//  Copyright (c) 2015-2019 Frank Fesevur                                  //
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

#include "../NPP/PluginInterface.h"

class NppMessenger
{
public:
	NppMessenger();
	virtual ~NppMessenger();

	void		SetTabWidth(int width);
	void		SetUseTabs(bool usetabs);
	void		SetLanguage(LangType lang);
	LRESULT 	SendNppMsg(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0);
	LRESULT		SendSciMsg(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0);
	void		MenuCommand(UINT msg);

	int			_tabwidth;
	bool		_usetabs;
	LangType	_lang;
	UINT		_msg;
	WPARAM		_wparam;
	LPARAM		_lparam;
};
