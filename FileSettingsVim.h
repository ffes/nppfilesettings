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

#include <string>

class NppMessenger;

class FileSettingsVim
{
public:
	FileSettingsVim(NppMessenger* msgr, const std::string line);

	bool Parse();

private:
	NppMessenger* _msgr;
	std::string _line;

	bool FindInt(const std::string longvar, const std::string shortvar, int& value);
	bool FindBool(const std::string longvar, const std::string shortvar) noexcept;
	bool FindString(const std::string longvar, const std::string shortvar, std::string& value);
};
