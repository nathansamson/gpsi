INCLUDES = -I$(shell pwd)
CXXFLAGS = -Wall $(INCLUDES) -fPIC
LDFLAGS = 
LDTESTFLAGS = `pkg-config --libs cppunit`
CXXSOURCES = $(shell find . -type f -name '*.cpp' -not -wholename '*/tests/*')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
CXXTESTSOURCES = $(shell find . -type f -name '*.cpp')
CXXTESTOBJECTS = $(patsubst %.cpp,%.o,$(CXXTESTSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXTESTSOURCES))
LIB = libsi.so
TEST = sitest

.PHONY: all clean test docs

all: $(LIB)

$(LIB): $(CXXOBJECTS)
	$(CXX) $(LDFLAGS) -shared -o $@ $^

test: $(TEST)
	./$(TEST)

$(TEST): $(CXXTESTOBJECTS)
	$(CXX) $(LDTESTFLAGS) -o $@ $^
	
clean:
	$(RM) $(CXXTESTOBJECTS) $(LIB) $(TEST) $(DEPFILES)
	
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
