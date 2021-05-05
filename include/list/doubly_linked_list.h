#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *doubly_linked_list_t;
typedef uint8_t doubly_linked_list_element_t;

/**
 * Initialize an doubly_linked_list of `n` elements.
 *
 * @return positive integer if success, -1 if operation fails.
 */
int8_t doubly_linked_list_init(doubly_linked_list_t *llist);

/**
 * Size
 */
uint8_t doubly_linked_list_length(doubly_linked_list_t llist);
bool doubly_linked_list_is_empty(doubly_linked_list_t llist);
bool doubly_linked_list_is_full(doubly_linked_list_t llist);

/**
 * Retrieve elements from the list
 */
doubly_linked_list_element_t doubly_linked_list_first(doubly_linked_list_t llist);
doubly_linked_list_element_t doubly_linked_list_last(doubly_linked_list_t llist);
doubly_linked_list_element_t doubly_linked_list_get(doubly_linked_list_t llist, uint8_t n);

/**
 * Insert
 */
int8_t doubly_linked_list_insert(doubly_linked_list_t llist, uint8_t n, doubly_linked_list_element_t elem);
int8_t doubly_linked_list_append(doubly_linked_list_t llist, doubly_linked_list_element_t elem);
int8_t doubly_linked_list_prepend(doubly_linked_list_t llist, doubly_linked_list_element_t elem);

/**
 * Remove
 */
void doubly_linked_list_remove(doubly_linked_list_t llist, uint8_t n);
void doubly_linked_list_clear(doubly_linked_list_t llist);

/**
 * Find
 */
int8_t doubly_linked_list_locate(doubly_linked_list_t llist, doubly_linked_list_element_t elem,
			 int8_t(*cmp)(doubly_linked_list_element_t a, doubly_linked_list_element_t b));

/**
 * Destroy the `doubly_linked_list`. It must be called then the doubly
 * linked list won't be used anymore.
 */
void doubly_linked_list_destroy(doubly_linked_list_t *llist);

#endif	/* DOUBLY_LINKED_LIST_H */
