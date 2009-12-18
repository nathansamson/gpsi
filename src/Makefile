INCLUDES = -I$(shell pwd) -I../
CXXFLAGS += $(INCLUDES) -fPIC -DTIXML_USE_TICPP
LDFLAGS = -L../tinyxml/ -lticpp
LDTESTFLAGS = $(LDFLAGS) `pkg-config --libs cppunit`
CXXSOURCES = $(shell find . -type f -name '*.cpp' -not -wholename '*/tests/*') $(TINYXMLSRCS)
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
CXXTESTSOURCES = $(shell find . -type f -name '*.cpp') $(TINYXMLSRCS)
CXXTESTOBJECTS = $(patsubst %.cpp,%.o,$(CXXTESTSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXTESTSOURCES))
LIB = libsi.so
TEST = sitest

.PHONY: all clean test

all: $(LIB)

$(LIB): $(CXXOBJECTS)
	$(CXX) $(LDFLAGS) -shared -o $@ $^

test: $(TEST)
	./$(TEST)

$(TEST): $(CXXTESTOBJECTS)
	$(CXX) -o $@ $^ $(LDTESTFLAGS)
	
clean:
	$(RM) $(CXXTESTOBJECTS) $(LIB) $(TEST) $(DEPFILES) $(shell find -name "*.d.*")
	
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
