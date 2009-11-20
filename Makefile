.PHONY: sdlgui zabbr lib test docs

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

clean:
	make -C zabbr clean
	make -C sdl clean
	make -C src clean
