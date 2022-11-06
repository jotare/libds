CHANGELOG
=========

0.21.0
------
- List modules now use `status_t` to report operation status

0.20.0
------
- Add constants module with initial constant definitions for libds

0.19.0
------
- Refactor graph API
- Graph module now represents labeled graphs

0.18.0
------
- Rename graph parameter on graph functions

0.17.0
------
- Add directed and undirected graph implementations using adjacency
  lists and adjacency matrix

0.16.0
------
- Add priority queue interface and implementation using a heap

0.15.0
------
- Add map implementation: closed hash table

0.14.0
------
- Dynamically sized open hash table

0.13.0
------
- Add map implementation: open hash table

0.12.0
------
- Add map interface

0.11.0
------
- Add indent as formatter and set a make target to format code

0.10.0
------
- Change uint8_t and int8_t types to standard int types

0.9.1
-----
- Fix linked list set destroy

0.9.0
-----
- Add linked list set implementation

0.8.0
-----
- Implement `length` and `is_empty` on bit vector sets

0.7.0
-----
- Use const when needed in all data structures

0.6.0
-----
- Add set interface header
- Add set tests
- Add bit_vector implementation of basic interface

0.5.0
-----
- Add makefile rules to build the library

0.4.2
-----
- Call destroy function at the end of all tests

0.4.1
-----
- Add list append and prepend test
- Fix bug in linked list insert in position 0

0.4.0
-----
- Added data structures interfaces for list, stack and queue
- Improved testing with CUnit, now all the project is tested under
  multiple test suites using one executable

0.3.0
-----
- Added static and dynamic queues

0.2.0
-----
- Added static and dynamic stacks

0.1.0
-----
- libds dev started :)
- Added Makefile
- Added array_list, linked_list and doubly_linked_list
