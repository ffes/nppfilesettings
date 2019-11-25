#include <catch2/catch.hpp>
#include "../NPP/PluginInterface.h"
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
