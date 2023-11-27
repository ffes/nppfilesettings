# NppFileSettings

NppFileSettings is plug-in for [Notepad++](https://notepad-plus-plus.org/)
that tries to recognize VIM modelines and adjust settings for that file accordingly.


## Currently supported

### Support for [VIM modelines](http://vim.wikia.com/wiki/Modeline_magic)

- `tabstop`, `ts`: set the width of tabstops
- `expandtab`, `et`: tab key produces spaces
- `noexpandtab`, `noet`: tab key produces tabs
- `filetype`, `ft`, `syntax`, `syn`: specify the syntax highlighting used for the file
- `fileformat`, `ff`: force the line ending to `unix`, `dos` or `mac`.
- `fileencoding`, `fenc`: support the following file encoding, based on the [vim docs](https://vimdoc.sourceforge.net/htmldoc/mbyte.html#mbyte-encoding)
  - `latin1`
  - `utf-8`
  - `utf-16`
  - `utf-16le`


## Planned

- Support more VIM modelines options, if possible
  - `wrap` and `nowrap` to wrap or don't wrap lines
  - `textwidth`, `tw` (at what column does the text wrap, default to `SCI_GETEDGECOLUMN`)
  - `shiftwidth`, `sw` can probably be mapped to `SCI_SETINDENT`
  - `spell` and `nospell` to enable or disable the spelling check
  - `spelllang` to set the spelling language

The `wrap` options need some work. This is a global setting in Notepad++ and
it needs to be preserved when switching between files.

The [DSpellCheck plugin](https://github.com/Predelnik/DSpellCheck) first needs to have
[an API](https://github.com/Predelnik/DSpellCheck/issues/309) to support the spell check
related properties.


## Not planned

### vim modeline `encoding`

There will be no support for `encoding` in vim modelines, which is different from `fileencoding`, because the [vim documentation](https://vimdoc.sourceforge.net/htmldoc/options.html#'encoding') clearly states

> This option cannot be set from a |[modeline](https://vimdoc.sourceforge.net/htmldoc/options.html#modeline)|. It would most likely corrupt the text.

### Notepad++ modeline format

I have no intention to create yet another modeline variant especially for Notepad++.
There are already too many of them.


## Wish List

- Support the modeline concept found in other places

  - [Emacs File Variables](https://www.gnu.org/software/emacs/manual/html_node/emacs/Specifying-File-Variables.html), see [#3](https://github.com/ffes/nppfilesettings/issues/3)
  - [Kate Editor](https://kate-editor.org/2006/02/09/kate-modelines/)
  - [Sublime Text](https://github.com/SublimeText/Modelines)
  - [jEdit](https://www.jedit.org/users-guide/buffer-local.html)
  - [PEP 263](https://peps.python.org/pep-0263), see [#4](https://github.com/ffes/nppfilesettings/issues/4)

- Add a dialog to show which settings are active for the current document.

- [Modeline Generator](https://www.wireshark.org/tools/modelines.html)
  to add a modeline, compatible with your editor of choice,
  to the current file or edit the existing one.


## Caveats

- Every time a file is activated (like when switching tabs), the plug-in
  will do its thing, not just when the file is opened. When a file is saved
  the plug-in is not activated (yet).

- The modeline parser is very basic. The fact that this plug-in recognizes
  something doesn't mean it is valid for `vim`. So when you add a modeline
  be sure to check its syntax with the real thing.

- If your `vim` doesn't recognize the modelines, you probably need to enable it.
  Add these lines to `~/.vimrc`:

  ```vim
  set modeline
  set modelines=5
  ```


## Known Issues

- This plug-in could cause unexpected results if you use it together with
  the [EditorConfig](https://editorconfig.org/) plug-in. When both plug-ins
  are installed and a `.editorconfig` file exists and sets tabs and a VIM
  modeline with tab settings is opened, it depends on the order the are
  found in the `Plugins` menu of Notepad++ which plug-in does its thing
  first. To fix this these two plugins need to become aware of each other
  most likely with the message `NPPM_MSGTOPLUGIN`. EditorConfig should be
  applied first (global) and the modeline after that (local).


## History

This plug-in used to be called NppFileMagic. It was also able to set the
language of a file based on the first line of the file. But since v6.8.4 Notepad++
recognizes many languages by itself by parsing the first line of a file. The
detection was not that great, so I contributed some of my code and knowledge
upstream and now that part of the plug-in was not needed anymore. Therefore I
decided to remove that code and rename to plug-in.
