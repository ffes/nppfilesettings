NppFileMagic
============

NppFileMagic is plug-in for Notepad++ for someone who works on cross platform projects that is inspired by file(1) and libmagic(3).
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

- `tabstop`, `ts`: set the tab width
- `expandtab`, `et`: tab key produces spaces
- `noexpandtab`, `noet` tab key produces tabs

Planned
-------

* Support more VIM modelines items, if possible
	- `wrap` (wrap lines)
	- `nowrap` (don't wrap lines)
	- `textwidth`, `tw` (at what line does the text wrap)
	- `filetype`, `ft`, `syntax`, `syn` (specify the syntax highlighting used for the file)

Wish List
---------

* Support the modeline concept found in [Emacs](http://www.gnu.org/software/emacs/manual/html_node/emacs/Specifying-File-Variables.html) and [Kate Editor](http://kate-editor.org/2006/02/09/kate-modelines/) and maybe other editors as well.

* File based language type recognition:

	First hard-coded, later configurable

	- `Makefile.in`		(Make)
	- `.gitconfig`		(INI)
	- `.git/config`		(INI)
	- `.bashrc`			(bash)
	- `.bash_profile`	(bash)
	- `.bash_logout`	(bash)

* Modeline Generator to add a modeline to the current file or edit the existing one.

Known Bugs
----------

* This plug-in could cause unexpected results if you use it together with the [EditorConfig](http://editorconfig.org/) plug-in. When both plug-ins are installed and a `.editorconfig` file exists and sets tabs and a VIM modeline with tab settings is opened, it depends on the order the are found in the `Plugins` menu of Notepad++ which plug-in does its thing first. To fix this these two plugins need to become aware of each other most likely with the message `NPPM_MSGTOPLUGIN`.
* Every time a file is activated (like when switching tabs), the plug-in will do its thing, not just when the file is opened. When a file is saved the plug-in is not actived (yet).
