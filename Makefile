.PHONY: sdlgui zabbr lib test docs docsupload memcheck

all: lib zabbr sdlgui

lib:
	make -C src all

test:
	make -C src test

zabbr:
	make -C zabbr all

sdlgui: lib zabbr
	make -C sdl all

docs:
	doxygen > /dev/null

docsupload: docs
	lftp -f docs-upload.lftp

memcheck: sdlgui
	LD_LIBRARY_PATH=./src valgrind --leak-check=full --suppressions=./sdl.sup ./sdl/sisdl
	
run: sdlgui
	LD_LIBRARY_PATH=./src ./sdl/sisdl

clean:
	make -C zabbr clean
	make -C sdl clean
	make -C src clean
