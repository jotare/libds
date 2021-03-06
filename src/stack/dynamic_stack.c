#include <stdlib.h>

#include "stack/dynamic_stack.h"

typedef struct node_t {
    struct node_t *prev;
    dynamic_stack_element_t elem;
} node_t;

typedef struct {
    node_t *top;
    uint8_t n;
} _stack_t;


int8_t dynamic_stack_init(dynamic_stack_t *dstack) {
    _stack_t *stack;

    stack = malloc(sizeof(_stack_t));
    if (stack == NULL)
	return -1;

    stack->n = 0;
    *dstack = stack;

    return 0;
}

uint8_t dynamic_stack_length(dynamic_stack_t dstack) {
    _stack_t *stack = dstack;
    return stack->n;
}

bool dynamic_stack_is_empty(dynamic_stack_t dstack) {
    _stack_t *stack = dstack;
    return stack->n == 0;
}

bool dynamic_stack_is_full(dynamic_stack_t dstack) {
    return false;
}

dynamic_stack_element_t dynamic_stack_top(dynamic_stack_t dstack) {
    _stack_t *stack = dstack;
    return stack->top->elem;
}

int8_t dynamic_stack_push(dynamic_stack_t dstack, dynamic_stack_element_t elem) {
    _stack_t *stack = dstack;
    node_t *node;

    node = malloc(sizeof(node_t));
    if (node == NULL)
	return -1;
 
    node->elem = elem;
    node->prev = stack->top;
    stack->top = node;
    stack->n++;

    return 0;
}

dynamic_stack_element_t dynamic_stack_pop(dynamic_stack_t dstack) {
    _stack_t *stack = dstack;
    node_t *node;
    dynamic_stack_element_t elem;

    node = stack->top;
    elem = node->elem;
    stack->top = node->prev;
    stack->n--;

    return elem;
}

void dynamic_stack_clear(dynamic_stack_t dstack) {
    while (!dynamic_stack_is_empty(dstack))
	dynamic_stack_pop(dstack);
}

void dynamic_stack_destroy(dynamic_stack_t *dstack) {
    _stack_t *stack = *dstack;
    dynamic_stack_clear(stack);
    free(stack);
    *dstack = NULL;
}
