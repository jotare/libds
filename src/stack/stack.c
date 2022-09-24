#include <stdlib.h>

#include "stack/static_stack.h"
#include "stack/dynamic_stack.h"
#include "stack/stack.h"

typedef struct {
    stack_type_t type;
    void *stack;
} stack_header_t;

typedef struct {
    int (*init)(stack_t * stack, unsigned int n);
    unsigned int (*length)(stack_t stack);
    bool (*is_empty)(stack_t stack);
    bool (*is_full)(stack_t stack);
      stack_element_t(*top) (stack_t stack);
    int (*push)(stack_t stack, stack_element_t elem);
      stack_element_t(*pop) (stack_t stack);
    void (*clear)(stack_t stack);
    void (*destroy)(stack_t * stack);
} istack_t;

static const istack_t static_stack = {
    static_stack_init,
    static_stack_length,
    static_stack_is_empty,
    static_stack_is_full,
    static_stack_top,
    static_stack_push,
    static_stack_pop,
    static_stack_clear,
    static_stack_destroy
};


static int
_dynamic_stack_init(dynamic_stack_t * dstack, unsigned int fake_n)
{
    return dynamic_stack_init(dstack);
}

static const istack_t dynamic_stack = {
    _dynamic_stack_init,
    dynamic_stack_length,
    dynamic_stack_is_empty,
    dynamic_stack_is_full,
    dynamic_stack_top,
    dynamic_stack_push,
    dynamic_stack_pop,
    dynamic_stack_clear,
    dynamic_stack_destroy
};

static const istack_t *
interface(stack_type_t type)
{
    switch (type) {
    case STATIC_STACK:
        return &static_stack;
    case DEFAULT_STACK:
    case DYNAMIC_STACK:
    default:
        return &dynamic_stack;
    }
}

int
stack_init(stack_t * stack, unsigned int n, stack_type_t type)
{
    stack_header_t *header;
    const istack_t *ds = interface(type);

    header = malloc(sizeof(stack_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init(&(header->stack), n);

    if (status < 0)
        *stack = NULL;
    else
        *stack = header;

    return status;
}

void
stack_destroy(stack_t * stack)
{
    stack_header_t *header;
    const istack_t *ds;

    header = *stack;
    ds = interface(header->type);

    ds->destroy(&(header->stack));
    free(header);
    *stack = NULL;
}

#define call_stack_interface_function(fun, s, ...)      \
    ({                                                  \
        stack_header_t *header = s;                     \
        istack_t const *ds = interface(header->type);   \
        return ds->fun(header->stack, ## __VA_ARGS__);  \
    })


unsigned int
stack_length(stack_t stack)
{
    call_stack_interface_function(length, stack);
}

bool
stack_is_empty(stack_t stack)
{
    call_stack_interface_function(is_empty, stack);
}

bool
stack_is_full(stack_t stack)
{
    call_stack_interface_function(is_full, stack);
}

stack_element_t
stack_top(stack_t stack)
{
    call_stack_interface_function(top, stack);
}

int
stack_push(stack_t stack, stack_element_t elem)
{
    call_stack_interface_function(push, stack, elem);
}

stack_element_t
stack_pop(stack_t stack)
{
    call_stack_interface_function(pop, stack);
}

void
stack_clear(stack_t stack)
{
    call_stack_interface_function(clear, stack);
}
