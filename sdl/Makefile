INCLUDES = -I$(shell pwd)
CXXFLAGS = -Wall $(INCLUDES)
LDFLAGS = 
CXXSOURCES = $(shell find . -type f -name '*.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
EXE = sisdl

.PHONY: all clean

all: $(EXE)

$(EXE): $(CXXOBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(CXXTESTOBJECTS) $(EXE) $(DEPFILES)
	
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
