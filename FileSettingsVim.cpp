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
#include <string>

#include "NPP/PluginInterface.h"
#include "NppFileSettings.h"
#include "FileSettingsVim.h"

/////////////////////////////////////////////////////////////////////////////
//

FileSettingsVim::FileSettingsVim(const char* line) : FileSettings()
{
	_line = line;
}

/////////////////////////////////////////////////////////////////////////////
// Based on /usr/share/vim/vim80/syntax

static LangType VimLangToNppLang(std::string lang)
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
	if (lang == "haskell")			return L_HASKELL;
	if (lang == "html")				return L_HTML;
	if (lang == "xhtml")			return L_HTML;
	//L_IHEX
	if (lang == "dosini")			return L_INI;
	if (lang == "iss")				return L_INNO;
	if (lang == "java")				return L_JAVA;
	//L_JS
	if (lang == "javascript")		return L_JAVASCRIPT;
	if (lang == "json")				return L_JSON;
	if (lang == "jsp")				return L_JSP;
	if (lang == "kix")				return L_KIX;
	//L_LATEX
	if (lang == "lisp")				return L_LISP;
	if (lang == "lua")				return L_LUA;
	if (lang == "make")				return L_MAKEFILE;
	if (lang == "matlab")			return L_MATLAB;
	if (lang == "mmix")				return L_MMIXAL;
	//L_NIMROD
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
	if (sscanf_s(pos + len + 1, "%d", &value) == 1)
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
//

std::string FileSettingsVim::FindStringWorker(const char* var)
{
	const char* pos = strstr(_line, var);
	if (pos == NULL)
		return "";

	int len = strlen(var);
	if (pos[len] != '=')
		return "";
	pos += len + 1;

	std::string value;
	while (*pos != 0)
	{
		if (isalnum(*pos))
			value += *pos;
		else
			break;
		pos++;
	}

	return value;
}

/////////////////////////////////////////////////////////////////////////////
//

std::string FileSettingsVim::FindString(const char* longvar, const char* shortvar)
{
	std::string value = FindStringWorker(longvar);
	if (value != "")
		return value;

	return FindStringWorker(shortvar);
}

/////////////////////////////////////////////////////////////////////////////
// *Very* basic implementation of a vim modeline parser

bool FileSettingsVim::Parse()
{
	// Is this a vim modeline?
	if (strstr(_line, " vi:") == NULL && strstr(_line, " vim:") == NULL && strstr(_line, " ex:") == NULL)
		return false;

	// Search for tab stop settings
	SetTabWidth(FindInt("tabstop", "ts"));

	// Search for tab expand settings
	if (FindBool("noexpandtab", "noet"))
		SetUseTabs(true);
	else if (FindBool("expandtab", "et"))
		SetUseTabs(false);

	// Search for filetype and syntax to set the language for syntax highlighting
	std::string langVIM = FindString("filetype", "ft");
	if (langVIM == "")
		langVIM = FindString("syntax", "syn");
	if (langVIM != "")
	{
		LangType langNPP = VimLangToNppLang(langVIM);
		if (langNPP != L_EXTERNAL)
			SetLanguage(langNPP);
	}

	return true;
}
