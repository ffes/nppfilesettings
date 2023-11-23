#include <catch2/catch.hpp>
#include "../NPP/PluginInterface.h"
#include "../NPP/menuCmdID.h"
#include "../FileSettingsVim.h"
#include "Mock/NppMessenger.h"

TEST_CASE("Vim::Parse(), ts=4")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: ts=4");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._tabwidth == 4);
}

TEST_CASE("Vim::Parse(), tabstop=4")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: tabstop=4");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._tabwidth == 4);
}

TEST_CASE("Vim::Parse(), filetype=dosini")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: filetype=dosini");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._lang == L_INI);
}

TEST_CASE("Vim::Parse(), filetype=random")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: filetype=random");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._lang == L_EXTERNAL);
}

TEST_CASE("Vim::Parse(), expandtab")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: expandtab");

	msgr._usetabs = true;
	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == false);
}

TEST_CASE("Vim::Parse(), noexpandtab")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: noexpandtab");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == true);
}

TEST_CASE("Vim::Parse(), et")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: et");

	msgr._usetabs = true;
	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == false);
}

TEST_CASE("Vim::Parse(), noet")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: noet");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == true);
}

TEST_CASE("Vim::Parse(), et ts=6")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: et ts=6");

	msgr._usetabs = true;
	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == false);
	REQUIRE(msgr._tabwidth == 6);
}

TEST_CASE("Vim::Parse(), fileformat=dos")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: fileformat=dos");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._msg == IDM_FORMAT_TODOS);
}

TEST_CASE("Vim::Parse(), ff=unix")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: ff=unix");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._msg == IDM_FORMAT_TOUNIX);
}

TEST_CASE("Vim::Parse(), fileencoding=utf-16")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: fileencoding=utf-16");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._msg == IDM_FORMAT_CONV2_UTF_16BE);
}

TEST_CASE("Vim::Parse(), fenc=utf-8")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: fenc=utf-8");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._msg == IDM_FORMAT_CONV2_AS_UTF_8);
}

TEST_CASE("Vim::Parse(), empty line")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "");

	const bool res = vim.Parse();
	REQUIRE(res == false);
}

TEST_CASE("Vim::Parse(), random line")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "some random text");

	const bool res = vim.Parse();
	REQUIRE(res == false);
}
