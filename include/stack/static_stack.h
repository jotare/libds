#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *static_stack_t;
typedef unsigned int static_stack_element_t;

/**
 * Initialize a static stack of `n` elements
 * 
 * @return positive integer if success, -1 if operation fails.
 */
int static_stack_init(static_stack_t * sstack, unsigned int n);

/**
 * Size
 */
unsigned int static_stack_length(const static_stack_t sstack);
bool static_stack_is_empty(const static_stack_t sstack);
bool static_stack_is_full(const static_stack_t sstack);

/**
 * Stack operations
 */
static_stack_element_t static_stack_top(const static_stack_t sstack);
int static_stack_push(static_stack_t sstack, static_stack_element_t elem);
static_stack_element_t static_stack_pop(static_stack_t sstack);

void static_stack_clear(static_stack_t sstack);

/**
 * Destroy the `static_stack`. It must be called when the stack won't
 * be used anymore.
*/
void static_stack_destroy(static_stack_t * sstack);

#endif /* STATIC_STACK_H */
