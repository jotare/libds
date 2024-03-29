# libds

## Yet another C data structures library

*libds* is a C library implementing common data structures like lists,
stacks, queues, sets, graphs...

If you are interested in common algorithms built on top of *libds*,
check out [libposidonia](https://github.com/jotare/libposidonia)

## Use libds

The library can be used in two different ways. The first one is using
the implementation modules independently, for example, use the `linked
list` module by its own. The second one is using interface modules like
`list`. Using this higher level modules is beneficial as you can
change the data structure interpretation in run-time.

To build the *libds* library execute:
```
make lib
```
A static library file `libds.a` will be created in the root
directory.

### Header files

*libds* has two main header files:

- *libds.h* includes only abstraction modules (list, stack, queue, set...)
- *libds-ext.h* includes implementation modules (linked list, dynamic
  stack, adjacency matrix directed graph...)

The recommended way to work is always using the main header file
*libds.h* and use the abstractions to be more implementation
resilient.

## Implemented data structures

*libds* implements de following data structures:

- List
  - Array list
  - Linked list
  - Doubly liked list
- Stack
  - Static (array) stack
  - Dynamic stack
- Queue
  - Static (array) queue
  - Dynamic queue
- Set
  - Bit vector
  - Linked list set
- Map
  - Open hash table
  - Closed hash table
- Priority queue
  - Heap
- Graph (labeled)
  - Directed graph
    - Adjacency matrix
    - Adjacency lists
  - Undirected graphs
    - Adjacency matrix
    - Adjacency lists

## Testing with CUnit

Al testing is performed with CUnit framework. Al tests are inside the
test directory. There, the main file `test_libds.c` joins all test
suites and execute them.

To run all tests execute:
```
make run-tests
```
it will build and link all necessary targets and run the tests.

## Formatting

GNU indent is used to format code. The Makefile has a `format` target
to format all code (headers, sources and tests). Please, use `make
format` before any contribution to the code.
