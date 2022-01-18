/**
 * @file stack.h
 * @brief Stack interface
 */
#ifndef STACK_H
#define STACK_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *stack_t;
typedef uint8_t stack_element_t;
typedef enum {DEFAULT_STACK, STATIC_STACK, DYNAMIC_STACK} stack_type_t;


/**
 * Initialize a stack of `n` elements
 * @return positive integer if success, -1 if operation fails.
 */
int8_t stack_init(stack_t *stack, uint8_t n, stack_type_t type);

/**
 * Size
 */
uint8_t stack_length(const stack_t stack);
bool stack_is_empty(const stack_t stack);
bool stack_is_full(const stack_t stack);

/**
 * Stack operations
 */
stack_element_t stack_top(const stack_t stack);
int8_t stack_push(stack_t stack, stack_element_t elem);
stack_element_t stack_pop(stack_t stack);

void stack_clear(stack_t stack);

/**
 * Destroy the `stack`. It must be called when the stack won't
 * be used anymore.
*/
void stack_destroy(stack_t *stack);

#endif  /* STACK_H */
