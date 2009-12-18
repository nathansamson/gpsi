INCLUDES = -I$(shell pwd) 
CXXFLAGS += $(INCLUDES) -DTIXML_USE_TICPP
CXXSOURCES = $(shell find . -maxdepth 1 -type f -name '*.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
LIB = libticpp.a
SUBDIRS = 

.PHONY: all clean $(SUBDIRS)

all: $(LIB)

$(SUBDIRS):
	$(MAKE) -C $@ $(MFLAGS)

$(LIB): $(SUBDIRS) $(CXXOBJECTS)
	$(AR) rc $@ $(shell find . -type f -name '*.o')

clean:
	@for i in $(SUBDIRS); do ($(MAKE) -C $$i $(MFLAGS) clean); done
	$(RM) $(CXXOBJECTS) $(LIB) $(DEPFILES) $(shell find -name "*.d.*") $(shell find -name "*~")

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
