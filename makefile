MAKE 				= make

CUSTOM_LIBS 		= $(wildcard custom_objects/*/)
CUSTOM_LIBS_DEBUG 	= $(patsubst %,%_DEBUG,$(CUSTOM_LIBS))

DIRS 				= $(wildcard sources/*/)
DIRS_DEBUG 			= $(patsubst %,%_DEBUG,$(DIRS))
MAKEFLAGS 			+= -j4


.PHONY: all debug $(CUSTOM_LIBS) $(CUSTOM_LIBS_DEBUG) $(DIRS) $(DIRS_DEBUG)
all: clean $(CUSTOM_LIBS) $(DIRS)
debug: clean $(CUSTOM_LIBS_DEBUG) $(DIRS_DEBUG)

$(CUSTOM_LIBS):
	$(MAKE) -C $@

$(CUSTOM_LIBS_DEBUG):
	$(MAKE) -C $(patsubst %_DEBUG,%,$@)

$(DIRS):
	$(MAKE) -C $@

$(DIRS_DEBUG):
	$(MAKE) -C $(patsubst %_DEBUG,%,$@)

clean:
	-rm -f custom_objects/*.o
	-rm -f build/*.elf
