#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *linked_list_t;
typedef int linked_list_element_t;

/**
 * Initialize an linked_list.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int linked_list_init(linked_list_t * llist);

/**
 * Size
 */
unsigned int linked_list_length(const linked_list_t llist);
bool linked_list_is_empty(const linked_list_t llist);
bool linked_list_is_full(const linked_list_t llist);

/**
 * Retrieve elements from the list
 */
linked_list_element_t linked_list_first(const linked_list_t llist);
linked_list_element_t linked_list_last(const linked_list_t llist);
linked_list_element_t linked_list_get(const linked_list_t llist,
                                      unsigned int n);

/**
 * Insert
 */
int linked_list_insert(linked_list_t llist, unsigned int n,
                       linked_list_element_t elem);
int linked_list_append(linked_list_t llist, linked_list_element_t elem);
int linked_list_prepend(linked_list_t llist, linked_list_element_t elem);

/**
 * Remove
 */
linked_list_element_t linked_list_remove(linked_list_t llist, unsigned int n);
void linked_list_clear(linked_list_t llist);

/**
 * Find
 */
int linked_list_locate(const linked_list_t llist, linked_list_element_t elem,
                       int (*cmp)(linked_list_element_t a,
                                  linked_list_element_t b));

/**
 * Destroy the `linked_list`. It must be called then the linked list
 * won't be used anymore.
 */
void linked_list_destroy(linked_list_t * llist);

#endif /* LINKED_LIST_H */
