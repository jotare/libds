# Makefile
# Author: jare

headers := $(wildcard include/*/*.h)   # include/*/z.h
sources := $(wildcard src/*/*.c)       # src/*/z.c
tests   := $(wildcard test/*/test_*.c) # test/*/test_z.c

source_objects := $(subst .c,.o,$(sources)) # src/*/z.o
test_objects   := $(subst .c,.o,$(tests))   # test/*/test_z.o

test_targets := $(basename $(tests)) # test/*/test_z

includes  := include/ $(dir $(wildcard include/*/)) $(dir $(wildcard test/)) $(dir $(wildcard test/*/))
libraries := cunit

CC := gcc
CFLAGS := -Wall -g -std=c99
# CPPFLAGS
CPPFLAGS += $(addprefix -I,$(includes))

# LDFLAGS
LDFLAGS += $(addprefix -L,$(libraries))
LDLIBS += $(addprefix -l,$(libraries))


.PHONY: all
all: tests
	@echo ALL


# sources



# tests
.PHONY: test
run-tests: tests
	./test/test_libds

tests: test/test_libds
test/test_libds: test/test_libds.o test/list/test_list.o src/list/list.o src/list/array_list.o src/list/linked_list.o src/list/doubly_linked_list.o

# tests: test_lists test_stacks test_queues

test_lists: test/list/test_array_list test/list/test_linked_list test/list/test_doubly_linked_list
test/list/test_array_list: src/list/array_list.o test/list/test_array_list.o
test/list/test_linked_list: src/list/linked_list.o test/list/test_linked_list.o
test/list/test_doubly_linked_list: src/list/doubly_linked_list.o test/list/test_doubly_linked_list.o

test_stacks: test/stack/test_static_stack test/stack/test_dynamic_stack
test/stack/test_static_stack: src/stack/static_stack.o test/stack/test_static_stack.o
test/stack/test_dynamic_stack: src/stack/dynamic_stack.o test/stack/test_dynamic_stack.o

test_queues: test/queue/test_static_queue test/queue/test_dynamic_queue 
test/queue/test_static_queue: src/queue/static_queue.o test/queue/test_static_queue.o
test/queue/test_dynamic_queue: src/queue/dynamic_queue.o test/queue/test_dynamic_queue.o



# cleaning
.PHONY: clean veryclean
clean:
	$(RM) depend
	find . -type f -name "*~" -exec rm {} +

veryclean: clean
	$(RM) $(source_objects) $(test_objects) $(test_targets)



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
