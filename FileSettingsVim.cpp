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

#include <windows.h>
#include <regex>

#include "NPP/PluginInterface.h"
#include "NPP/menuCmdID.h"
#include "NppFileSettings.h"
#include "FileSettingsVim.h"

#ifdef USE_CATCH2
#include "Tests/Mock/NppMessenger.h"
#else
#include "NppMessenger.h"
#endif

/**
 * Constructor
 *
 * @param [in] msgr The instance of NppMessenger
 * @param [in] line The line where a VIM modeline needs to searched for
 */

FileSettingsVim::FileSettingsVim(NppMessenger* msgr, const std::string line)
{
	_msgr = msgr;
	_line = line;
}

/**
 * Convert the VIM lang into a Notepad++ LangType
 *
 * @param [in] lang The language in the vim modeline
 *
 * @return The corresponding Notepad++ language
 *
 * @remark Largely based on /usr/share/vim/vim80/syntax
 *         The filenames in that directory are the words that need to be used as vim language.
 */

LangType FileSettingsVim::VimLangToNppLang(std::string lang)
{
	// Go through all the languages we know of
	if (lang == "ada")				return L_ADA;
	if (lang == "asm")				return L_ASM;
	if (lang == "aspvbs")			return L_ASP;
	if (lang == "asn")				return L_ASN1;
	//L_AU3
	//L_AVS
	if (lang == "baan")				return L_BAANC;
	if (lang == "sh")				return L_BASH;
	if (lang == "dosbatch")			return L_BATCH;
	//L_BLITZBASIC
	if (lang == "c")				return L_C;
	if (lang == "ocaml")			return L_CAML;
	if (lang == "cmake")			return L_CMAKE;
	if (lang == "cobol")			return L_COBOL;
	//L_COFFEESCRIPT
	if (lang == "cpp")				return L_CPP;
	if (lang == "cs")				return L_CS;
	//L_CSOUND
	if (lang == "css")				return L_CSS;
	if (lang == "d")				return L_D;
	if (lang == "diff")				return L_DIFF;
	if (lang == "erlang")			return L_ERLANG;
	//L_ESCRIPT
	//L_FLASH
	if (lang == "forth")			return L_FORTH;
	if (lang == "fortran")			return L_FORTRAN;
	//L_FORTRAN_77
	//L_FREEBASIC
	//L_GDSCRIPT
	if (lang == "haskell")			return L_HASKELL;
	if (lang == "hollywood")		return L_HOLLYWOOD;
	if (lang == "html")				return L_HTML;
	if (lang == "xhtml")			return L_HTML;
	//L_IHEX
	if (lang == "dosini")			return L_INI;
	if (lang == "iss")				return L_INNO;
	if (lang == "java")				return L_JAVA;
	//L_JS
	if (lang == "javascript")		return L_JAVASCRIPT;
	if (lang == "json")				return L_JSON;
	//L_JSON5
	if (lang == "jsp")				return L_JSP;
	if (lang == "kix")				return L_KIX;
	//L_LATEX
	if (lang == "lisp")				return L_LISP;
	if (lang == "lua")				return L_LUA;
	if (lang == "make")				return L_MAKEFILE;
	if (lang == "matlab")			return L_MATLAB;
	if (lang == "mmix")				return L_MMIXAL;
	//L_MSSQL
	//L_NIM
	if (lang == "crontab")			return L_NNCRONTAB;
	if (lang == "nsis")				return L_NSIS;
	if (lang == "objc")				return L_OBJC;
	//L_OSCRIPT
	if (lang == "pascal")			return L_PASCAL;
	if (lang == "perl")				return L_PERL;
	if (lang == "perl6")			return L_PERL;
	if (lang == "php")				return L_PHP;
	//L_POWERSHELL
	if (lang == "postscr")			return L_PS;
	//L_PUREBASIC
	if (lang == "python")			return L_PYTHON;
	if (lang == "r")				return L_R;
	if (lang == "rc")				return L_RC;
	if (lang == "rebol")			return L_REBOL;
	if (lang == "registry")			return L_REGISTRY;
	if (lang == "ruby")				return L_RUBY;
	if (lang == "rust")				return L_RUST;
	if (lang == "scheme")			return L_SCHEME;
	if (lang == "st")				return L_SMALLTALK;
	if (lang == "spice")			return L_SPICE;
	if (lang == "sql")				return L_SQL;
	if (lang == "sqloracle")		return L_SQL;
	if (lang == "srec")				return L_SREC;
	//L_SWIFT
	if (lang == "tcl")				return L_TCL;
	//L_TEHEX
	if (lang == "tex")				return L_TEX;
	if (lang == "typescript")		return L_TYPESCRIPT;
	//L_TXT2TAGS
	if (lang == "vb")				return L_VB;
	if (lang == "basic")			return L_VB;
	if (lang == "verilog")			return L_VERILOG;
	if (lang == "prolog")			return L_VISUALPROLOG;
	if (lang == "vhdl")				return L_VHDL;
	if (lang == "docbk")			return L_XML;
	if (lang == "dtd")				return L_XML;
	if (lang == "sgml")				return L_XML;
	if (lang == "xml")				return L_XML;
	if (lang == "xsd")				return L_XML;
	if (lang == "xslt")				return L_XML;
	if (lang == "yaml")				return L_YAML;

	// (Yet) unrecognized language
	return L_EXTERNAL;
}

/**
 * Search the line for the long and short version of an integer setting
 *
 * @param [in] longvar  The long variant of the setting to search for
 * @param [in] shortvar The short variant of the setting to search for
 * @param [out] value   The value of the setting
 *
 * @return Is the setting found?
 */

bool FileSettingsVim::FindInt(const std::string longvar, const std::string shortvar, int& value)
{
	using namespace std;

	// Search for (longvar=|shortvar=)(\d+)
	string r = "(";
	r += longvar;
	r += "=|";
	r += shortvar;
	r += "=)(\\d+)";

	regex re(r);
	smatch m;
	if (regex_search(_line, m, re))
	{
		// There should be three values, in [0] is the whole match
		// In the following items are the separate matches
		if (m.size() == 3)
		{
			// In the second must be the number we are looking for
			value = stoi(m[2]);
			return true;
		}
	}
	return false;
}

/**
 * Search the line for the long and short version of a boolean setting
 *
 * @param [in] longvar  The long variant of the setting to search for
 * @param [in] shortvar The short variant of the setting to search for
 *
 * @return Was the setting found?
 */

bool FileSettingsVim::FindBool(const std::string longvar, const std::string shortvar) noexcept
{
	return (_line.find(longvar) != std::string::npos || _line.find(shortvar) != std::string::npos);
}

/**
 * Search the line for the long and short version of a string setting
 *
 * @param [in] longvar  The long variant of the setting to search for
 * @param [in] shortvar The short variant of the setting to search for
 * @param [out] value   The value of the setting
 *
 * @return Is the setting found?
 */

bool FileSettingsVim::FindString(const std::string longvar, const std::string shortvar, std::string& value)
{
	using namespace std;

	// Search for (longvar=|shortvar=)(\S+)
	string r = "(";
	r += longvar;
	r += "=|";
	r += shortvar;
	r += "=)(\\S+)";

	regex re(r);
	smatch m;
	if (regex_search(_line, m, re))
	{
		// There should be three values, in [0] is the whole match
		// In the following items are the separate matches
		if (m.size() == 3)
		{
			// In the second one must be the string we are looking for
			value = m[2];
			return true;
		}
	}
	return false;
}

/**
 * Very basic implementation of a vim modeline parser
 *
 * @return Is the current line a vim modeline?
 */

bool FileSettingsVim::Parse()
{
	// Is this a vim modeline?
	if (_line.find(" vi:") == std::string::npos && _line.find(" vim:") == std::string::npos && _line.find(" ex:") == std::string::npos)
		return false;

	// Search for tab stop settings
	int tabwidth = 0;
	if (FindInt("tabstop", "ts", tabwidth))
		_msgr->SetTabWidth(tabwidth);

	// Search for tab expand settings, expanding tabs mean "use spaces when tab is pressed"
	if (FindBool("noexpandtab", "noet"))
		_msgr->SetUseTabs(true);
	else if (FindBool("expandtab", "et"))
		_msgr->SetUseTabs(false);

	// Search for filetype and syntax to set the language for syntax highlighting
	std::string langVIM;
	if (FindString("filetype", "ft", langVIM) || FindString("syntax", "syn", langVIM))
	{
		const LangType langNPP = VimLangToNppLang(langVIM);
		if (langNPP != L_EXTERNAL)
			_msgr->SetLanguage(langNPP);
	}

	// Set the file encoding, based on
	// https://vimdoc.sourceforge.net/htmldoc/mbyte.html#mbyte-encoding
	std::string encoding;
	if (FindString("fileencoding", "fenc", encoding))
	{
		if (encoding == "latin1")
			_msgr->SendNppMsg(NPPM_MENUCOMMAND, 0, IDM_FORMAT_CONV2_ANSI);
		else if (encoding == "utf-8")
			_msgr->SendNppMsg(NPPM_MENUCOMMAND, 0, IDM_FORMAT_CONV2_AS_UTF_8);
		else if (encoding == "utf-16")
			_msgr->SendNppMsg(NPPM_MENUCOMMAND, 0, IDM_FORMAT_CONV2_UTF_16BE);
		else if (encoding == "utf-16le")
			_msgr->SendNppMsg(NPPM_MENUCOMMAND, 0, IDM_FORMAT_CONV2_UTF_16LE);
	}

	return true;
}
