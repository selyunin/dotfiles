
" An example for a vimrc file.
"
" Maintainer:	Bram Moolenaar <Bram@vim.org>
" Last change:	2011 Apr 15
"
" To use it, copy it to
"     for Unix and OS/2:  ~/.vimrc
"	      for Amiga:  s:.vimrc
"  for MS-DOS and Win32:  $VIM\_vimrc
"	    for OpenVMS:  sys$login:.vimrc

" When started as "evim", evim.vim will already have done these settings.
if v:progname =~? "evim"
  finish
endif

syntax on " syntax highlighting
" Use Vim settings, rather than Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible
filetype plugin on

" allow backspacing over everything in insert mode
set backspace=indent,eol,start

if has("vms")
  set nobackup		" do not keep a backup file, use versions instead
else
  set backup		" keep a backup file
endif
set history=1000	" store tonn of history

" added by selyunin
" line numbers
set number
" highlight search results
set hlsearch
" Use case insensitive search
set ignorecase
" When opening a new line and no filetype-specific indenting is enabled, keep
" the same indent as the line you're currently on. Useful for READMEs, etc.
set autoindent
" Enable use of the mouse for all modes
set mouse=a
" Display the cursor position on the last line of the screen or in the status
" line of a window
set ruler
" size of a hard tabstop
set tabstop=4
" size of an "indent"
set shiftwidth=4

set virtualedit=onemore  " allow for cursor beyond last character
set showcmd		" display incomplete commands
highlight LineNr term=bold cterm=NONE ctermfg=DarkGrey ctermbg=NONE gui=NONE guifg=DarkGrey guibg=NONE
"set background=dark
"colorscheme solarized
set undodir=~/.vimbackup,.
set backupdir=~/.vimbackup,.
set directory=~/.vimbackup,.
set undofile		" so is persistent undo ...
set undolevels=1000	"maximum number of changes that can be undone
set undoreload=10000 	"maximum number lines to save for undo on a buffer reload
set incsearch		" do incremental searching
set showmode		" display the current mode

set cursorline		" highlight current line
hi cursorline guibg=#333333	 " highlight bg color of current line
hi CursorColumn guibg=#333333	 " highlight cursor
" For Win32 GUI: remove 't' flag from 'guioptions': no tearoff menu entries
" let &guioptions = substitute(&guioptions, "t", "", "g")
set scrolloff=3 	" minimum lines to keep above and below cursor
" Don't use Ex mode, use Q for formatting
	if has('cmdline_info')
		set ruler " show the ruler
		set rulerformat=%30(%=\:b%n%yd%m%r%w\ %l,%c%V\ %P%) " a ruler on steroids
		set showcmd " show partial commands in status line and
		" selected characters/lines in visual mode
	endif
	
	

map Q gq
nnoremap <C-J> o<Esc>
nnoremap <C-K> O<Esc>
" nmap <F7> o<Esc>
" nmap <F8> O<Esc>
nnoremap <silent> <F8> :TlistToggle<CR>
nmap <C-I> i<CR><Esc>
" CTRL-U in insert mode deletes a lot.  Use CTRL-G u to first break undo,
" so that you can undo CTRL-U after inserting a line break.
inoremap <C-U> <C-G>u<C-U>

" In many terminal emulators the mouse works just fine, thus enable it.
if has('mouse')
  set mouse=a
endif

" Switch syntax highlighting on, when the terminal has colors
" Also switch on highlighting the last used search pattern.
if &t_Co > 2 || has("gui_running")
  syntax on
  set hlsearch
endif

" Only do this part when compiled with support for autocommands.
if has("autocmd")

  " Enable file type detection.
  " Use the default filetype settings, so that mail gets 'tw' set to 72,
  " 'cindent' is on in C files, etc.
  " Also load indent files, to automatically do language-dependent indenting.
  filetype plugin indent on

  " Put these in an autocmd group, so that we can delete them easily.
  augroup vimrcEx
  au!

  " For all text files set 'textwidth' to 78 characters.
  autocmd FileType text setlocal textwidth=78

  " When editing a file, always jump to the last known cursor position.
  " Don't do it when the position is invalid or when inside an event handler
  " (happens when dropping a file on gvim).
  " Also don't do it when the mark is in the first line, that is the default
  " position when opening a file.
  autocmd BufReadPost *
    \ if line("'\"") > 1 && line("'\"") <= line("$") |
    \   exe "normal! g`\"" |
    \ endif

  augroup END

else

  set autoindent		" always set autoindenting on
  
endif " has("autocmd")

" Toggle spell checking on and off with `,s`
let mapleader = ","
nmap <silent> <leader>s :set spell!<CR>

" Toggle text width 70 and wrap with `,t`
let mapleader = ","
nmap <silent> <leader>t :set tw=70<CR> :set wrap<CR>

" Convenient command to see the difference between the current buffer and the
" file it was loaded from, thus the changes you made.
" Only define it when not defined already.
if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r ++edit # | 0d_ | diffthis
		  \ | wincmd p | diffthis
endif

" IMPORTANT: grep will sometimes skip displaying the file name if you
" search in a singe file. This will confuse Latex-Suite. Set your grep
" program to always generate a file-name.
set grepprg=grep\ -nH\ $*

" OPTIONAL: Starting with Vim 7, the filetype of empty .tex files defaults to
" 'plaintex' instead of 'tex', which results in vim-latex not being loaded.
" The following changes the default filetype back to 'tex':
let g:tex_flavor='latex'

" language tool jar path
let g:languagetool_jar='/home/selyunin/Downloads/LanguageTool-2.2/languagetool-commandline.jar'