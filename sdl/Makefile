INCLUDES = -I$(shell pwd) `pkg-config --cflags sdl` -I../ -I../zabbr -I../src -I../tinyxml
CXXFLAGS += $(INCLUDES) -DTIXML_USE_TICPP
LDFLAGS += `pkg-config --libs sdl` -lSDL_gfx -lSDL_ttf -lSDL_image -L../zabbr -lzabbr -L../src -lsi -L../tinyxml -lticpp
CXXSOURCES = $(shell find . -type f -name '*.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
EXE = gpsi

.PHONY: all clean ../zabbr/zabbr.a

all: $(EXE)

$(EXE): $(CXXOBJECTS) ../zabbr/zabbr.a
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

clean:
	$(RM) $(CXXOBJECTS) $(EXE) $(DEPFILES) $(shell find -name "*.d.*") $(shell find -name "*~")

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    #Chances are, these files don't exist.  GMake will create them and
    #clean up automatically afterwards
    -include $(DEPFILES)
endif
