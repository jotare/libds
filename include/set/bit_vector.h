#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *bit_vector_t;
typedef int bit_vector_element_t;

/**
 * Initialize an empty bit vector with a universe consisting of 0..n-1
 * integer elements.
 * @return positive integer or 0 if success, negative one if fails
 */
int bit_vector_init (bit_vector_t * bv, int n);

/**
 * Size
 */
unsigned int bit_vector_length (const bit_vector_t bv);
bool bit_vector_is_empty (const bit_vector_t bv);

/**
 * Membership, insertion and deletion operations on a bit vector `bv`.
 */
bool bit_vector_member (bit_vector_t bv, bit_vector_element_t e);
int bit_vector_insert (bit_vector_t bv, bit_vector_element_t e);
int bit_vector_delete (bit_vector_t bv, bit_vector_element_t e);
void bit_vector_clear (bit_vector_t bv);

/**
 * Perform UNION, INTERSECTION and DIFFERENCE bit vector operations between
 * `a` and `b` storing the result in an initialized bit vector `c`. If `c` is
 * not initialized, unexpected behavior might happen.
 * @return positive integer or 0 if success, negative one if fails
*/
int bit_vector_union (const bit_vector_t a, const bit_vector_t b,
                      bit_vector_t * c);
int bit_vector_intersection (const bit_vector_t a, const bit_vector_t b,
                             bit_vector_t * c);
int bit_vector_difference (const bit_vector_t a, const bit_vector_t b,
                           bit_vector_t * c);

/**
 * Destroy the bit vector `bv`. It must be called when the bit vector won't
 * be used anymore.
 */
void bit_vector_destroy (bit_vector_t * bv);

void bit_vector_print (const bit_vector_t bv);

#endif /* BIT_VECTOR_H */
