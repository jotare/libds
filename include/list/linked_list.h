#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *linked_list_t;
typedef uint8_t linked_list_element_t;

/**
 * Initialize an linked_list.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int8_t linked_list_init(linked_list_t *llist);

/**
 * Size
 */
uint8_t linked_list_length(linked_list_t llist);
bool linked_list_is_empty(linked_list_t llist);
bool linked_list_is_full(linked_list_t llist);

/**
 * Retrieve elements from the list
 */
linked_list_element_t linked_list_first(linked_list_t llist);
linked_list_element_t linked_list_last(linked_list_t llist);
linked_list_element_t linked_list_get(linked_list_t llist, uint8_t n);

/**
 * Insert
 */
int8_t linked_list_insert(linked_list_t llist, uint8_t n, linked_list_element_t elem);
int8_t linked_list_append(linked_list_t llist, linked_list_element_t elem);
int8_t linked_list_prepend(linked_list_t llist, linked_list_element_t elem);

/**
 * Remove
 */
linked_list_element_t linked_list_remove(linked_list_t llist, uint8_t n);
void linked_list_clear(linked_list_t llist);

/**
 * Find
 */
int8_t linked_list_locate(linked_list_t llist, linked_list_element_t elem,
			 int8_t(*cmp)(linked_list_element_t a, linked_list_element_t b));

/**
 * Destroy the `linked_list`. It must be called then the linked list
 * won't be used anymore.
 */
void linked_list_destroy(linked_list_t *llist);

#endif	/* LINKED_LIST_H */
