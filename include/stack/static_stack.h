#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <inttypes.h>
#include <stdbool.h>

typedef void* static_stack_t;
typedef uint8_t static_stack_element_t;

/**
 * Initialize a static stack of `n` elements
 * 
 * @return positive integer if success, -1 if operation fails.
 */
int8_t static_stack_init(static_stack_t *sstack, uint8_t n);

/**
 * Size
 */
uint8_t static_stack_length(static_stack_t sstack);
bool static_stack_is_empty(static_stack_t sstack);
bool static_stack_is_full(static_stack_t sstack);

/**
 * Stack operations
 */
static_stack_element_t static_stack_top(static_stack_t sstack);
int8_t static_stack_push(static_stack_t sstack, static_stack_element_t elem);
static_stack_element_t static_stack_pop(static_stack_t sstack);

void static_stack_clear(static_stack_t sstack);

/**
 * Destroy the `static_stack`. It must be called when the stack won't
 * be used anymore.
*/
void static_stack_destroy(static_stack_t *sstack);

#endif	/* STATIC_STACK_H */
