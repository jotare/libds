#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *bit_vector_t;
typedef int bit_vector_element_t;

/**
 * Initialize an empty bit_vector with a universe consisting of 0..n-1
 * integer elements.
 * @return positive integer or 0 if success, negative one if fails
 */
int8_t bit_vector_init(bit_vector_t *bv, int n);

/**
 * Membership, insertion and deletion operations on a bit_vector `bv`.
 */
bool bit_vector_member(bit_vector_t bv, bit_vector_element_t e);
int8_t bit_vector_insert(bit_vector_t bv, bit_vector_element_t e);
int8_t bit_vector_delete(bit_vector_t bv, bit_vector_element_t e);
void bit_vector_clear(bit_vector_t bv);

/**
 * Perform UNION, INTERSECTION and DIFFERENCE bit_vector operations between
 * `a` and `b` storing the result in an initialized bit_vector `c`. If `c` is
 * not initialized, unexpected behavior might happen.
 * @return positive integer or 0 if success, negative one if fails
*/
int8_t bit_vector_union(bit_vector_t a, bit_vector_t b, bit_vector_t *c);
int8_t bit_vector_intersection(bit_vector_t a, bit_vector_t b, bit_vector_t *c);
int8_t bit_vector_difference(bit_vector_t a, bit_vector_t b, bit_vector_t *c);

/**
 * Destroy the bit_vector `bv`. It must be called when the bit_vector won't
 * be used anymore.
 */
void bit_vector_destroy(bit_vector_t *bv);


#endif /* BIT_VECTOR_H */
