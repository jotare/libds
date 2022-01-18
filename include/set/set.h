/**
 * @file set.h
 * @brief Set interface
 */
#ifndef SET_H
#define SET_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *set_t;
typedef int set_element_t;
typedef enum { DEFAULT_SET, BIT_VECTOR_SET } set_type_t;

/**
 * Initialize an empty set with a universe consisting of 0..n-1 integer elements.
 * @return positive integer or 0 if success, negative one if fails
 */
int8_t set_init(set_t *set, int n, set_type_t type);

/**
 * Membership, insertion and deletion operations on a set `set`.
 */
bool set_member(set_t set, set_element_t e);
int8_t set_insert(set_t set, set_element_t e);
int8_t set_delete(set_t set, set_element_t e);
void set_clear(set_t set);

/**
 * Perform UNION, INTERSECTION and DIFFERENCE set operations between
 * `a` and `b` storing the result in an initialized set `c`. If `c` is
 * not initialized, unexpected behavior might happen.
 * @return positive integer or 0 if success, negative one if fails
*/
int8_t set_union(const set_t a, const set_t b, set_t *c);
int8_t set_intersection(const set_t a, const set_t b, set_t *c);
int8_t set_difference(const set_t a, const set_t b, set_t *c);

/**
 * Destroy the set `set`. It must be called when the set won't be used
 * anymore.
 */
void set_destroy(set_t *set);

#endif /* SET_H */
