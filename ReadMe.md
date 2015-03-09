NppFileMagic
============

NppFileMagic is plugin for Notepad++ that is inspired by file(1) and libmagic(3)
It tries to determine the file type of a file when it is opened and set the language type.

Currently supported:
SheBang (#!)
- bash
- php
- python
- perl
- ruby
XML

Planned:

Support for VIM modelines. When ts/tabstop is set in a vim modeline, use those settings for that document.


File based language type recognition:

First hard-coded, later configurable
Makefile.in			(Make)
.gitconfig			(INI)
.git/config			(INI)
.bashrc				(bash)
.bash_profile		(bash)
.bash_logout		(bash)


The current status of this plugin is just a proof of concept. It only works for the first file opened.
Plugin messages are being processed in a strange way. When the message NPPN_FILEOPENED is fired the message NPPM_GETFULLCURRENTPATH does not return the name of the new file because after the NPPN_FILEOPENED the focus is still on the previous tab (and thus previous file).
