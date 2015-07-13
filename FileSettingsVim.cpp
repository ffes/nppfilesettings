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
#include <stdio.h>
#include <string.h>

#include "NPP/PluginInterface.h"
#include "NppFileMagic.h"
#include "FileSettingsVim.h"

/////////////////////////////////////////////////////////////////////////////
//

FileSettingsVim::FileSettingsVim(const char* line)
{
	_line = line;
}

/////////////////////////////////////////////////////////////////////////////
// Search for "var" and when found return the value that the "var" is to

int FileSettingsVim::FindIntWorker(const char* var)
{
	const char* pos = strstr(_line, var);
	if (pos == NULL)
		return 0;

	int len = strlen(var);
	if (pos[len] != '=')
		return 0;

	int value;
	if (sscanf(pos + len + 1, "%d", &value) == 1)
		return value;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Search the line for the long and short version of an integer setting

int FileSettingsVim::FindInt(const char* longvar, const char* shortvar)
{
	int value = FindIntWorker(longvar);
	if (value != 0)
		return value;

	return FindIntWorker(shortvar);
}

/////////////////////////////////////////////////////////////////////////////
// Search the line for the long and short version of a boolean setting

bool FileSettingsVim::FindBool(const char* longvar, const char* shortvar)
{
	// First look for longvar
	const char* pos = strstr(_line, longvar);
	if (pos != NULL)
		return true;

	// Not found, so look for shortvar
	return strstr(_line, shortvar) != NULL;
}

/////////////////////////////////////////////////////////////////////////////
// *Very* basic implementation of a vim modeline parser

bool FileSettingsVim::Parse()
{
	// Is this a vim modeline?
	if (strstr(_line, " vi:") == NULL && strstr(_line, " vim:") == NULL && strstr(_line, " ex:") == NULL)
		return false;

	// Search for tab stop settings
	int tabstop = FindInt("tabstop", "ts");
	if (tabstop > 0)
		SendMsg(SCI_SETTABWIDTH, tabstop);

	// Search for tab expand settings
	if (FindBool("noexpandtab", "noet"))
		SendMsg(SCI_SETUSETABS, 1);
	else if (FindBool("expandtab", "et"))
		SendMsg(SCI_SETUSETABS, 0);

	return true;
}
