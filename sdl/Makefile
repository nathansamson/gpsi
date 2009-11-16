INCLUDES = -I$(shell pwd) `pkg-config --cflags sdl SDL_gfx`
CXXFLAGS = -Wall $(INCLUDES) -Werror -g
LDFLAGS = `pkg-config --libs sdl SDL_gfx`
CXXSOURCES = $(shell find . -type f -name '*.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
EXE = sisdl

.PHONY: all clean

all: $(EXE)

$(EXE): $(CXXOBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^
	
clean:
	$(RM) $(CXXOBJECTS) $(EXE) $(DEPFILES)
	
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
