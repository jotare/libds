#include <stdlib.h>

#include "stack/static_stack.h"

typedef struct {
    static_stack_element_t *stack;
    unsigned int n;             /* number of elements */
    unsigned int size;          /* stack size */
} _stack_t;


int
static_stack_init(static_stack_t * sstack, unsigned int n)
{
    _stack_t *stack;

    stack = malloc(sizeof(_stack_t));
    if (stack == NULL)
        return -1;

    stack->stack = calloc(n, sizeof(static_stack_element_t));
    if (stack->stack == NULL) {
        free(stack);
        return -1;
    }

    stack->n = 0;
    stack->size = n;
    *sstack = stack;

    return 0;
}

unsigned int
static_stack_length(const static_stack_t sstack)
{
    _stack_t *stack = sstack;

    return stack->n;
}

bool
static_stack_is_empty(const static_stack_t sstack)
{
    _stack_t *stack = sstack;

    return stack->n == 0;
}

bool
static_stack_is_full(const static_stack_t sstack)
{
    _stack_t *stack = sstack;

    return stack->n == stack->size;
}

static_stack_element_t
static_stack_top(const static_stack_t sstack)
{
    _stack_t *stack = sstack;

    return stack->stack[stack->n - 1];
}

int
static_stack_push(static_stack_t sstack, static_stack_element_t elem)
{
    _stack_t *stack = sstack;

    stack->stack[stack->n] = elem;
    stack->n++;

    return 0;
}

static_stack_element_t
static_stack_pop(static_stack_t sstack)
{
    _stack_t *stack = sstack;
    static_stack_element_t elem;

    elem = stack->stack[stack->n - 1];
    stack->n--;

    return elem;
}

void
static_stack_clear(static_stack_t sstack)
{
    while (!static_stack_is_empty(sstack))
        static_stack_pop(sstack);
}

void
static_stack_destroy(static_stack_t * sstack)
{
    _stack_t *stack = *sstack;

    free(stack->stack);
    free(stack);
    *sstack = NULL;
}
