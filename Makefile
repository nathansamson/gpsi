export CXXFLAGS += -Werror -Wall

.PHONY: sdlgui zabbr lib test docs docsupload memcheck run

all: lib zabbr sdlgui

lib:
	$(MAKE) -C src all

test:
	$(MAKE) -C src test

zabbr:
	$(MAKE) -C zabbr all

sdlgui: lib zabbr
	$(MAKE) -C sdl all

docs:
	doxygen > /dev/null

docsupload: docs
	lftp -f docs-upload.lftp

memcheck: sdlgui
	LD_LIBRARY_PATH=./src valgrind --leak-check=full --suppressions=./sdl.sup ./sdl/sisdl
	
run: sdlgui
	LD_LIBRARY_PATH=./src ./sdl/sisdl

clean:
	$(MAKE) -C zabbr clean
	$(MAKE) -C sdl clean
	$(MAKE) -C src clean
