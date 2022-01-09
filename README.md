# libds

## Yet another C data structures library

*libds* is a C library implementing common data structures.

## Use libds

The library can be used in two different ways. The first one is using
the implementation modules independently, for example, use the `linked
list` module by its own. The second one is using interface modules like
`list`. Using this higher level modules is beneficial as you can
change the data structure interpretation in run-time.

⚠️For the moment, a library file is not generated (it will be in the future).

## Testing with CUnit

Al testing is performed with CUnit framework. Al tests are inside the
test directory. There, the main file `test_libds.c` joins all test
suites and execute them.

To run all tests execute:
```
make run-tests
```
it will build all necessary targets and run the tests.
