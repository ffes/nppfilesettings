NppFileMagic
============

NppFileMagic is plugin for Notepad++ for someone who works on cross platform projects that is inspired by file(1) and libmagic(3)
It tries to determine the file type of a file when it is opened and set the language type.
It also tries to recognize VIM modelines and adjust settings for that file accordingly.

Currently supported
-------------------

**Set syntax highlighting base on information found in the first line of a file**

* [SheBang](https://en.wikipedia.org/wiki/Shebang_%28Unix%29) (`#!`)
	- bash
	- php
	- python
	- perl
	- ruby
* XML

**Support for [VIM modelines](http://vim.wikia.com/wiki/Modeline_magic)**

* `ts`: set the tab width

Planned
-------

* Support more VIM modelines items, if possible
	- `tabstop` (set the tab width)
	- `expandtab`, `et` (tab key produces tab)
	- `noexpandtab`, `noet` (tab key produces spaces)
	- `wrap` (wrap lines)
	- `nowrap` (don't wrap lines)
	- `textwidth`, `tw` (at what line does the text wrap)
	- `filetype`, `ft`, `syntax`, `syn`

* Support the modeline concept found in [Emacs](http://www.gnu.org/software/emacs/manual/html_node/emacs/Specifying-File-Variables.html) and [Kate Editor](http://kate-editor.org/2006/02/09/kate-modelines/).

* File based language type recognition:

	First hard-coded, later configurable

	- `Makefile.in`		(Make)
	- `.gitconfig`		(INI)
	- `.git/config`		(INI)
	- `.bashrc`			(bash)
	- `.bash_profile`	(bash)
	- `.bash_logout`	(bash)

Status
------

The current status of this plugin is just a proof of concept. It only works for the first file opened.
Notepad++ processes plugin messages in a strange way. When the message NPPN_FILEOPENED is fired the message NPPM_GETFULLCURRENTPATH does not return the name of the new file because after the NPPN_FILEOPENED the focus is still on the previous tab (and thus previous file).
