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
#include <stdio.h>
#include <string.h>

#include "NPP/PluginInterface.h"
#include "NppFileSettings.h"
#include "FileSettings.h"

/////////////////////////////////////////////////////////////////////////////
//

FileSettings::FileSettings()
{
}

/////////////////////////////////////////////////////////////////////////////
//

void FileSettings::SetTabStop(int tabstop)
{
	if (tabstop > 0)
		SendMsg(SCI_SETTABWIDTH, tabstop);
}

/////////////////////////////////////////////////////////////////////////////
//

void FileSettings::UseTabs(bool usetabs)
{
	SendMsg(SCI_SETUSETABS, usetabs ? 1 : 0);
}

/////////////////////////////////////////////////////////////////////////////
//

void FileSettings::SetLanguage(LangType lang)
{
	SendMessage(g_nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, lang);
}
