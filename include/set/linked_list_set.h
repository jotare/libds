#ifndef LINKED_LIST_SET_H
#define LINKED_LIST_SET_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *linked_list_set_t;
typedef int linked_list_set_element_t;

/**
 * Initialize an empty linked list set.
 * @return positive integer or 0 if success, negative one if fails
 */
int linked_list_set_init (linked_list_set_t * lls);

/**
 * Size
 */
unsigned int linked_list_set_length (const linked_list_set_t lls);
bool linked_list_set_is_empty (const linked_list_set_t lls);

/**
 * Membership, insertion and deletion operations on a linked list set
 * `lls`.
 */
bool linked_list_set_member (linked_list_set_t lls,
                             linked_list_set_element_t e);
int linked_list_set_insert (linked_list_set_t lls,
                            linked_list_set_element_t e);
int linked_list_set_delete (linked_list_set_t lls,
                            linked_list_set_element_t e);
void linked_list_set_clear (linked_list_set_t lls);

/**
 * Perform UNION, INTERSECTION and DIFFERENCE linked list set
 * operations between `a` and `b` storing the result in an initialized
 * linked list set `c`. If `c` is not initialized, unexpected behavior
 * might happen.
 * @return positive integer or 0 if success, negative one if fails
*/
int linked_list_set_union (const linked_list_set_t a,
                           const linked_list_set_t b, linked_list_set_t * c);
int linked_list_set_intersection (const linked_list_set_t a,
                                  const linked_list_set_t b,
                                  linked_list_set_t * c);
int linked_list_set_difference (const linked_list_set_t a,
                                const linked_list_set_t b,
                                linked_list_set_t * c);

/**
 * Destroy the linked list set `lls`. It must be called when the linked list set won't
 * be used anymore.
 */
void linked_list_set_destroy (linked_list_set_t * lls);

void linked_list_set_print (const linked_list_set_t lls);

#endif /* LINKED_LIST_SET_H */
