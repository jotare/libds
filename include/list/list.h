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
typedef uint8_t list_element_t; // TODO: change uint8_t to generic type
typedef enum {DEFAULT_LIST, ARRAY_LIST, LINKED_LIST, DOUBLY_LINKED_LIST} list_type_t;

/**
 * Initialize a `type` `list` of `n` elements. Use `n` = 0 when it's
 * possible to make an undefined length list.
 * @return status code indicating success of operation. If -1, the call failed.
 */
int8_t list_init(list_t *list, uint8_t n, list_type_t type);

/**
 * Size
 */
uint8_t list_length(list_t list);
bool list_is_empty(list_t list);
bool list_is_full(list_t list);

/**
 * Retrieve elements from the list
 */
list_element_t list_first(list_t list);
list_element_t list_last(list_t list);
list_element_t list_get(list_t list, uint8_t n);

/**
 * Insert
 */
int8_t list_insert(list_t list, uint8_t n, list_element_t elem);
int8_t list_append(list_t list, list_element_t elem);
int8_t list_prepend(list_t list, list_element_t elem);

/**
 * Remove
 */
list_element_t list_remove(list_t list, uint8_t n);
void list_clear(list_t list);

int8_t list_locate(list_t list, list_element_t elem,
			 int8_t(*cmp)(list_element_t a, list_element_t b));

/**
 * Destroy the list `list`. It must be called when the list won't be
 * used anymore.
 */
void list_destroy(list_t *list);

#endif	/* LIST_H */
