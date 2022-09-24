/**
 * @file list.h
 * @brief List abstract module
 *
 * The List module abstracts this common data structure. The list_init
 * function allows the user choosing the implementation in runtime.
 */

#ifndef LIST_H
#define LIST_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *list_t;
typedef int list_element_t;     // TODO: change unsigned int to generic type
typedef enum { DEFAULT_LIST, ARRAY_LIST, LINKED_LIST,
    DOUBLY_LINKED_LIST
} list_type_t;

/**
 * Initialize a `type` `list` of `n` elements. Use `n` = 0 when it's
 * possible to make an undefined length list.
 * @return status code indicating success of operation. If -1, the call failed.
 */
int list_init(list_t * list, unsigned int n, list_type_t type);

/**
 * Size
 */
unsigned int list_length(const list_t list);
bool list_is_empty(const list_t list);
bool list_is_full(const list_t list);

/**
 * Retrieve elements from the list
 */
list_element_t list_first(const list_t list);
list_element_t list_last(const list_t list);
list_element_t list_get(const list_t list, unsigned int n);

/**
 * Insert
 */
int list_insert(list_t list, unsigned int n, list_element_t elem);
int list_append(list_t list, list_element_t elem);
int list_prepend(list_t list, list_element_t elem);

/**
 * Remove
 */
list_element_t list_remove(list_t list, unsigned int n);
void list_clear(list_t list);

int list_locate(const list_t list, list_element_t elem,
                int (*cmp)(list_element_t a, list_element_t b));

/**
 * Destroy the list `list`. It must be called when the list won't be
 * used anymore.
 */
void list_destroy(list_t * list);

#endif /* LIST_H */
