#include <stdlib.h>

#include "stack/static_stack.h"

typedef struct {
    static_stack_element_t *stack;
    uint8_t n;			/* number of elements */
    uint8_t size;		/* stack size */
} _stack_t;


int8_t static_stack_init(static_stack_t *sstack, uint8_t n) {
    _stack_t *stack;

    stack = malloc(sizeof(_stack_t));
    if (stack == NULL)
	return -1;

    stack->stack = malloc(n*sizeof(static_stack_element_t));
    if (stack->stack == NULL) {
	free(stack);
	return -1;
    }

    stack->n = 0;
    stack->size = n;
    *sstack = stack;

    return 0;
}

uint8_t static_stack_length(static_stack_t sstack) {
    _stack_t *stack = sstack;
    return stack->n;
}

bool static_stack_is_empty(static_stack_t sstack) {
    _stack_t *stack = sstack;
    return stack->n == 0;
}

bool static_stack_is_full(static_stack_t sstack) {
    _stack_t *stack = sstack;
    return stack->n == stack->size;
}

static_stack_element_t static_stack_top(static_stack_t sstack) {
    _stack_t *stack = sstack;
    return stack->stack[stack->n-1];
}

int8_t static_stack_push(static_stack_t sstack, static_stack_element_t elem) {
    _stack_t *stack = sstack;

    stack->stack[stack->n] = elem;
    stack->n++;

    return 0;
}

static_stack_element_t static_stack_pop(static_stack_t sstack) {
    _stack_t *stack = sstack;
    static_stack_element_t elem;

    elem = stack->stack[stack->n-1];
    stack->n--;

    return elem;
}

void static_stack_clear(static_stack_t sstack) {
    while (!static_stack_is_empty(sstack))
	static_stack_pop(sstack);
}

void static_stack_destroy(static_stack_t *sstack) {
    _stack_t *stack = *sstack;
    free(stack->stack);
    free(stack);
    *sstack = NULL;
}
