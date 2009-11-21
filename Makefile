.PHONY: sdlgui zabbr lib test docs docsupload

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

clean:
	make -C zabbr clean
	make -C sdl clean
	make -C src clean
