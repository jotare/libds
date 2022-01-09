#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *array_list_t;
typedef uint8_t array_list_element_t;

/**
 * Initialize an array_list of `n` elements.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int8_t array_list_init(array_list_t *alist, uint8_t n);

/**
 * Size
 */
uint8_t array_list_length(array_list_t alist);
bool array_list_is_empty(array_list_t alist);
bool array_list_is_full(array_list_t alist);

/**
 * Retrieve elements
 */
array_list_element_t array_list_first(array_list_t alist);
array_list_element_t array_list_last(array_list_t alist);
array_list_element_t array_list_get(array_list_t alist, uint8_t n);

/**
 * Insert
 */
int8_t array_list_insert(array_list_t alist, uint8_t n, array_list_element_t elem);
int8_t array_list_append(array_list_t alist, array_list_element_t elem);
int8_t array_list_prepend(array_list_t alist, array_list_element_t elem);

/**
 * Remove
 */
array_list_element_t array_list_remove(array_list_t alist, uint8_t n);
void array_list_clear(array_list_t alist);

/**
 * Find
 */
int8_t array_list_locate(array_list_t alist, array_list_element_t elem,
			 int8_t(*cmp)(array_list_element_t a, array_list_element_t b));

/**
 * Destroy the `array_list`. It must be called then the array list
 * won't be used anymore.
 */
void array_list_destroy(array_list_t *alist);

#endif	/* ARRAY_LIST_H */
