.PHONY: sdlgui lib test docs

all: lib sdlgui

lib:
	make -C src all

test:
	make -C src test

sdlgui: lib
	make -C sdl all

docs:
	doxygen > /dev/null

clean:
	make -C sdl clean
	make -C src clean
