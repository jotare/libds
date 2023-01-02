/**
 * @file doubly_linked_list.h
 * @brief Doubly linked list implementation
 *
 * List implementation using a doubly linked list.
 * Refer to `list` module for more details about each operation.
 */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <inttypes.h>
#include <stdbool.h>

#include "../constants.h"

typedef void *doubly_linked_list_t;
typedef int doubly_linked_list_element_t;


status_t doubly_linked_list_init(doubly_linked_list_t * dlist);

unsigned int doubly_linked_list_length(const doubly_linked_list_t dlist);
bool doubly_linked_list_is_empty(const doubly_linked_list_t dlist);
bool doubly_linked_list_is_full(const doubly_linked_list_t dlist);

doubly_linked_list_element_t doubly_linked_list_first(const
                                                      doubly_linked_list_t
                                                      dlist);
doubly_linked_list_element_t doubly_linked_list_last(const
                                                     doubly_linked_list_t
                                                     dlist);
doubly_linked_list_element_t doubly_linked_list_get(const
                                                    doubly_linked_list_t
                                                    dlist, unsigned int n);

status_t doubly_linked_list_insert(doubly_linked_list_t dlist, unsigned int n,
                                   doubly_linked_list_element_t elem);
status_t doubly_linked_list_append(doubly_linked_list_t dlist,
                                   doubly_linked_list_element_t elem);
status_t doubly_linked_list_prepend(doubly_linked_list_t dlist,
                                    doubly_linked_list_element_t elem);

status_t doubly_linked_list_set(doubly_linked_list_t alist, unsigned int n,
                                doubly_linked_list_element_t elem);

doubly_linked_list_element_t doubly_linked_list_remove(doubly_linked_list_t
                                                       dlist, unsigned int n);
void doubly_linked_list_clear(doubly_linked_list_t dlist);

int doubly_linked_list_locate(const doubly_linked_list_t dlist,
                              doubly_linked_list_element_t elem,
                              int (*cmp)(doubly_linked_list_element_t a,
                                         doubly_linked_list_element_t b));

void doubly_linked_list_destroy(doubly_linked_list_t * dlist);

#endif /* DOUBLY_LINKED_LIST_H */
