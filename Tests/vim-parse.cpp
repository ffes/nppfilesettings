#include <catch2/catch.hpp>
#include "../NPP/PluginInterface.h"
#include "../FileSettingsVim.h"
#include "Mock_NppMessenger.h"

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

TEST_CASE("Vim::Parse(), ex")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: et");

	msgr._usetabs = true;
	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == false);
}

TEST_CASE("Vim::Parse(), noex")
{
	NppMessenger msgr;
	FileSettingsVim vim(&msgr, "# vim: noet");

	const bool res = vim.Parse();
	REQUIRE(res == true);
	REQUIRE(msgr._usetabs == true);
}
