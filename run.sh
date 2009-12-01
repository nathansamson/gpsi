if [ $DEBUG -eq 1 ]; then
	dbg="gdb --args"
else
	dbg=""
fi
LD_LIBRARY_PATH=./src $dbg ./sdl/sisdl $@
