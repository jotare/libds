#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *doubly_linked_list_t;
typedef int doubly_linked_list_element_t;

/**
 * Initialize an doubly_linked_list.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int doubly_linked_list_init(doubly_linked_list_t *dlist);

/**
 * Size
 */
unsigned int doubly_linked_list_length(const doubly_linked_list_t dlist);
bool doubly_linked_list_is_empty(const doubly_linked_list_t dlist);
bool doubly_linked_list_is_full(const doubly_linked_list_t dlist);

/**
 * Retrieve elements from the list
 */
doubly_linked_list_element_t doubly_linked_list_first(const doubly_linked_list_t dlist);
doubly_linked_list_element_t doubly_linked_list_last(const doubly_linked_list_t dlist);
doubly_linked_list_element_t doubly_linked_list_get(const doubly_linked_list_t dlist, unsigned int n);

/**
 * Insert
 */
int doubly_linked_list_insert(doubly_linked_list_t dlist, unsigned int n, doubly_linked_list_element_t elem);
int doubly_linked_list_append(doubly_linked_list_t dlist, doubly_linked_list_element_t elem);
int doubly_linked_list_prepend(doubly_linked_list_t dlist, doubly_linked_list_element_t elem);

/**
 * Remove
 */
doubly_linked_list_element_t doubly_linked_list_remove(doubly_linked_list_t dlist, unsigned int n);
void doubly_linked_list_clear(doubly_linked_list_t dlist);

/**
 * Find
 */
int doubly_linked_list_locate(const doubly_linked_list_t dlist, doubly_linked_list_element_t elem,
                                 int(*cmp)(doubly_linked_list_element_t a, doubly_linked_list_element_t b));

/**
 * Destroy the `doubly_linked_list`. It must be called then the doubly
 * linked list won't be used anymore.
 */
void doubly_linked_list_destroy(doubly_linked_list_t *dlist);

#endif	/* DOUBLY_LINKED_LIST_H */
