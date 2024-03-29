# Makefile
# Author: jotare

headers := $(wildcard include/*/*.h)   # include/*/z.h
sources := $(wildcard src/*/*.c)       # src/*/z.c
tests   := $(wildcard test/*/test_*.c) # test/*/test_z.c

source_objects := $(subst .c,.o,$(sources)) # src/*/z.o
test_objects   := $(subst .c,.o,$(tests))   # test/*/test_z.o

test_targets := $(basename $(tests)) # test/*/test_z

includes  := include/ $(dir $(wildcard include/)) $(dir $(wildcard test/))
libraries := cunit

CC := gcc
CFLAGS := -Wall -g -std=c99
CPPFLAGS += $(addprefix -I,$(includes))

LDFLAGS += $(addprefix -L,$(libraries))
LDLIBS += $(addprefix -l,$(libraries))


.PHONY: all
all: lib tests
	@echo ALL


# sources
lib: libds.a
libds.a: libds.a($(source_objects))


# tests
run-tests: tests
	./test/test_libds

tests: test/test_libds
test/test_libds: test/test_libds.o $(test_objects) $(source_objects)


# formatting
format:
	indent -bad -bap -sc -br -ce -brs -psl -blf -nut -i4 -npcs $(headers) $(sources) $(tests)


# cleaning
.PHONY: clean veryclean
clean:
	$(RM) depend
	find . -type f -name "*~" -exec rm {} +

veryclean: clean
	$(RM) $(source_objects) $(test_objects) $(test_targets) test/test_libds.o test/test_libds libds.a


# header dependencies
depend:  $(sources)
	@echo "Building and including dependencies..."
	@$(CC) -M $(CPPFLAGS) $^ | \
	sed -e 's,\([0-9A-Za-z_]*\)\.o[ :]*,build/\1.o: ,g' > $@

# targets whose don't build dependencies
exclude := clean veryclean all
excluded_goals := $(strip $(if $(MAKECMDGOALS), \
			$(foreach target,$(exclude), \
				$(if $(findstring $(target),$(MAKECMDGOALS)),$(target),)), \
			"default"))

ifeq "$(excluded_goals)" ""
  -include depend
endif


# source dependencies

directed_graph_adj_list.o: adj_list.o
undirected_graph_adj_list.o: adj_list.o

# debug info
.PHONY: debug
debug:
	@echo HEADERS
	@echo $(headers)
	@echo
	@echo SOURCES
	@echo $(sources)
	@echo
	@echo TESTS
	@echo $(tests)
	@echo
	@echo SOURCE_OBJECTS
	@echo $(source_objects)
	@echo
	@echo TEST_OBJECTS
	@echo $(test_objects)
	@echo
	@echo TEST_TARGETS
	@echo $(test_targets)
	@echo
	@echo INCLUDES
	@echo $(includes)
	@echo
	@echo LIBRARIES
	@echo $(libraries)
