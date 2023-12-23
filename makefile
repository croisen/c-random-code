MAKE 				= make
MAKEFLAGS 			+= -j4

CUSTOM_LIBS 		= $(wildcard custom_libs/*/)
CUSTOM_LIBS_DEBUG 	= $(patsubst %,%_DEBUG,$(CUSTOM_LIBS))

DIRS 				= $(wildcard sources/*/)
DIRS_DEBUG 			= $(patsubst %,%_DEBUG,$(DIRS))

TEST_LIBS 			= $(wildcard test/*/)


.PHONY: all debug test $(CUSTOM_LIBS) $(CUSTOM_LIBS_DEBUG) $(DIRS) \
	$(DIRS_DEBUG) $(TEST_LIBS)
all: clean $(CUSTOM_LIBS) $(DIRS)
debug: clean $(CUSTOM_LIBS_DEBUG) $(DIRS_DEBUG)
test: clean $(TEST_LIBS)

$(DIRS): clean $(CUSTOM_LIBS)
	$(MAKE) -C $@

$(DIRS_DEBUG): clean $(CUSTOM_LIBS_DEBUG)
	$(MAKE) debug -C $(patsubst %_DEBUG,%,$@)

$(TEST_LIBS): $(CUSTOM_LIBS)
	$(MAKE) -C $@

$(CUSTOM_LIBS):
	$(MAKE) -C $@

$(CUSTOM_LIBS_DEBUG):
	$(MAKE) debug -C $(patsubst %_DEBUG,%,$@)

clean:
	-rm -f custom_objects/*.o
	-rm -f test/*.elf
	-rm -f build/*.elf
