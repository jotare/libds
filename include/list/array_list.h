#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *array_list_t;
typedef int array_list_element_t;

/**
 * Initialize an array_list of `n` elements.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int array_list_init(array_list_t * alist, unsigned int n);

/**
 * Size
 */
unsigned int array_list_length(const array_list_t alist);
bool array_list_is_empty(const array_list_t alist);
bool array_list_is_full(const array_list_t alist);

/**
 * Retrieve elements
 */
array_list_element_t array_list_first(const array_list_t alist);
array_list_element_t array_list_last(const array_list_t alist);
array_list_element_t array_list_get(const array_list_t alist, unsigned int n);

/**
 * Insert
 */
int array_list_insert(array_list_t alist, unsigned int n,
                      array_list_element_t elem);
int array_list_append(array_list_t alist, array_list_element_t elem);
int array_list_prepend(array_list_t alist, array_list_element_t elem);

/**
 * Remove
 */
array_list_element_t array_list_remove(array_list_t alist, unsigned int n);
void array_list_clear(array_list_t alist);

/**
 * Find
 */
int array_list_locate(const array_list_t alist, array_list_element_t elem,
                      int (*cmp)(array_list_element_t a,
                                 array_list_element_t b));

/**
 * Destroy the `array_list`. It must be called then the array list
 * won't be used anymore.
 */
void array_list_destroy(array_list_t * alist);

#endif /* ARRAY_LIST_H */
