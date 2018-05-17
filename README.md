My LinuxBox configuration repo
============================================

1. [Description](#description)
2. [Bash](#bash)
3. [Vim](#vim)
4. [Git](#git)
5. [Maintainer](#maintainer)


### <a name="description"></a>1. Description

The repo holds configuration files to set up a LinuxBox.

### <a name="packages"></a>2. Bash

*  [`.inputrc`](./.inputrc) 

*  [`.bashrc`](./.bashrc)

*  [`.bash_aliases`](./.bash_aliases)

*  [`.bash_profile`](./.bash_profile)

### <a name="vim"></a>3. Vim

*  [`.vimrc`](./.vimrc)

*  [`.vim`](./.vim)


#### 3.2 Compile vim from source with the clipboard support

##### 3.2.1 Clone vim repo from the github:

`git clone git@github.com:vim/vim.git`

##### 3.2.2  install required libraries:

`libx11-dev libxtst-dev libxt-dev libsm-dev libxpm-dev ncurses-dev ctags`

##### 3.2.3 Locate where the required packages install their files.

Ubuntu:

`dpkg-query -L libxtst-dev`

OpenSuse:

`rpm -qa libxtst-dev`

##### 3.2.4  Configure with `X11` and specify path to the includes and libraries:

`./configure --with-x --x-includes=/usr/include/X11/ --x-libraries=/usr/lib/x86_64-linux-gnu/`

##### 3.2.5  Check if the configuration includes `X11` support. In the vim root folder do:

`grep X11 src/auto/config.h`

The response should look like:

`#define HAVE_X11`

And not like:

`/* #undef HAVE_X11 */`

##### 3.2.6 After compiling vim, check its options to ensure that `clipboard` option is enabled:

`vim --version`

+clipboard

##### 3.2.7  Set up vim runtime. 
Vim source folder contains relevant information 
that vim uses during runtime (`${vimroot}/runtime`). 
We need to point out `VIMRUNTIME` environment variable to this folder:
in the `~/.bashrc` file:

`export VIMRUNTIME='''path/to/vim/source'''/runtime`

### <a name="git"></a>4. Git

The two config files are copied from the official git repo ([link](https://github.com/git/git/tree/master/contrib/completion)):

*  [`.git-completion.bash`](./.git-completion.bash)

*  [`.git-prompt.sh`](./.git-prompt.sh)

### <a name="maintainer"></a>5. Maintainer

[Konstantin Selyunin](http://selyunin.com/), for
suggestions/questions/comments please contact: selyunin [dot] k [dot] v [at] gmail [dot] com
