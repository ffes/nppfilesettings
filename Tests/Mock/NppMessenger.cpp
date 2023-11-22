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

#include "Mock/NppMessenger.h"

NppMessenger::NppMessenger()
{
	_tabwidth = 0;
	_usetabs = false;
	_lang = L_EXTERNAL;
	_msg = 0;
	_lparam = 0;
	_wparam = 0;
}

NppMessenger::~NppMessenger()
{
}

void NppMessenger::SetTabWidth(int width)
{
	_tabwidth = width;
}

void NppMessenger::SetUseTabs(bool usetabs)
{
	_usetabs = usetabs;
}

void NppMessenger::SetLanguage(LangType lang)
{
	_lang = lang;
}

LRESULT NppMessenger::SendNppMsg(UINT msg, WPARAM wparam, LPARAM lparam)
{
	_msg = msg;
	_wparam = wparam;
	_lparam = lparam;

	return ERROR_SUCCESS;
}

LRESULT NppMessenger::SendSciMsg(UINT msg, WPARAM wparam, LPARAM lparam)
{
	_msg = msg;
	_wparam = wparam;
	_lparam = lparam;

	return ERROR_SUCCESS;
}
