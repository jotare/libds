#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *dynamic_stack_t;
typedef unsigned int dynamic_stack_element_t;

/**
 * Initialize a dynamic stack
 * 
 * @return positive integer if success, -1 if operation fails.
 */
int dynamic_stack_init (dynamic_stack_t * dstack);

/**
 * Size
 */
unsigned int dynamic_stack_length (const dynamic_stack_t dstack);
bool dynamic_stack_is_empty (const dynamic_stack_t dstack);
bool dynamic_stack_is_full (const dynamic_stack_t dstack);

/**
 * Stack operations
 */
dynamic_stack_element_t dynamic_stack_top (const dynamic_stack_t dstack);
int dynamic_stack_push (dynamic_stack_t dstack, dynamic_stack_element_t elem);
dynamic_stack_element_t dynamic_stack_pop (dynamic_stack_t dstack);

void dynamic_stack_clear (dynamic_stack_t dstack);

/**
 * Destroy the `dynamic_stack`. It must be called when the stack won't
 * be used anymore.
*/
void dynamic_stack_destroy (dynamic_stack_t * dstack);

#endif /* DYNAMIC_STACK_H */
