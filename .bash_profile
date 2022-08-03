function extract {
	local RED="\033[1;31m"
	local NO_COLOR="\033[0m"
	local GREEN="\033[1;32m"
 if [ -z "$1" ]; then
    # display usage if no parameters given
    echo -e "Usage: $RED extract $NO_COLOR <path/file_name>.<zip|rar|bz2|gz|tar|tbz2|tgz|Z|7z|xz|ex|tar.bz2|tar.gz|tar.xz>"
 else
    if [ -f $1 ] ; then
        # NAME=${1%.*}
        # mkdir $NAME && cd $NAME
        case $1 in
          *.tar.bz2)   tar xvjf $1    ;;
          *.tar.gz)    tar xvzf $1    ;;
          *.tar.xz)    tar xvJf $1    ;;
          *.lzma)      unlzma $1      ;;
          *.bz2)       bunzip2 $1     ;;
          *.rar)       unrar x -ad $1 ;;
          *.gz)        gunzip $1      ;;
          *.tar)       tar xvf $1     ;;
          *.tbz2)      tar xvjf $1    ;;
          *.tgz)       tar xvzf $1    ;;
          *.zip)       unzip $1       ;;
          *.Z)         uncompress $1  ;;
          *.7z)        7z x $1        ;;
          *.xz)        unxz $1        ;;
          *.exe)       cabextract $1  ;;
          *)           echo -e "$RED extract:$NO_COLOR '$1' - unknown archive method" ;;
        esac
    else
		echo -e "$RED $1 $NO_COLOR - file does not exist"
    fi
fi
}

function up( )
{
	LIMIT=$1
	P=$PWD
	for ((i=1; i <= LIMIT; i++))
	do
		P=$P/..
	done
	cd $P
	export MPWD=$P
}

function back( )
{
	LIMIT=$1
	P=$MPWD
	for ((i=1; i <= LIMIT; i++))
	do
		P=${P%/..}
	done
	cd $P
	export MPWD=$P
}

function lsize( )
{
	if [ -z "$1" ]; then
		du -a -h --max-depth=1 | sort -hr 
	else
		du -a -h --max-depth=1 | sort -hr | head -n $(($1 + 1))
	fi
}

function rsync_on_save( )
{
    SRC=$1
    DEST=$2

    prev_stat_result=`stat -c %Y $SRC/* | sort -n | tail -1`

    while true; do
        current_stat_result=`stat -c %Y $SRC/* | sort -n | tail -1`
        if [ $current_stat_result != $prev_stat_result ]; then
          rsync -avP $SRC/ $DEST
        fi
        sleep 0.7
        prev_stat_result=$current_stat_result
    done
}

function rsync_file_from_server( )
{
    FILE=$1
    SERVER=$2
    DEST=$2

    prev_stat_result=`ssh ${SERVER} stat -c %Y ${FILE} | tail -1`

    while true; do
        current_stat_result=`ssh ${SERVER} stat -c %Y ${FILE} | tail -1`
        if [ $current_stat_result != $prev_stat_result ]; then
          rsync -avP ${SERVER}:${FILE} $DEST
        fi
        sleep 0.7
        prev_stat_result=$current_stat_result
    done
}

