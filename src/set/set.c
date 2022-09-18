#include <bits/stdint-uintn.h>
#include <stdlib.h>

#include "set/bit_vector.h"
#include "set/linked_list_set.h"
#include "set/set.h"

typedef struct {
    set_type_t type;
    void *set;
} set_header_t;

typedef struct {
    int (*init) (set_t * set, int n);
    unsigned int (*length) (set_t set);
    bool (*is_empty) (set_t set);
    bool (*member) (set_t set, set_element_t e);
    int (*insert) (set_t set, set_element_t e);
    int (*delete) (set_t set, set_element_t e);
    void (*clear) (set_t set);
    int (*union_) (const set_t a, const set_t b, set_t * c);
    int (*intersection) (const set_t a, const set_t b, set_t * c);
    int (*difference) (const set_t a, const set_t b, set_t * c);
    void (*destroy) (set_t * set);
    void (*print) (const set_t set);
} iset_t;

static const iset_t bit_vector = {
    bit_vector_init,
    bit_vector_length,
    bit_vector_is_empty,
    bit_vector_member,
    bit_vector_insert,
    bit_vector_delete,
    bit_vector_clear,
    bit_vector_union,
    bit_vector_intersection,
    bit_vector_difference,
    bit_vector_destroy,
    bit_vector_print
};

static int
_linked_list_set_init (linked_list_set_t * lls, int fake_n)
{
    return linked_list_set_init (lls);
}

static const iset_t linked_list_set = {
    _linked_list_set_init,
    linked_list_set_length,
    linked_list_set_is_empty,
    linked_list_set_member,
    linked_list_set_insert,
    linked_list_set_delete,
    linked_list_set_clear,
    linked_list_set_union,
    linked_list_set_intersection,
    linked_list_set_difference,
    linked_list_set_destroy,
    linked_list_set_print,
};


static const iset_t *
interface (set_type_t type)
{
    switch (type) {
    case BIT_VECTOR_SET:
        return &bit_vector;

    case LINKED_LIST_SET:
        return &linked_list_set;

    case DEFAULT_SET:
    default:
        return &bit_vector;
    }
}

int
set_init (set_t * set, int n, set_type_t type)
{
    set_header_t *header;
    const iset_t *ds = interface (type);

    header = malloc (sizeof (set_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init (&(header->set), n);

    if (status < 0)
        *set = NULL;
    else
        *set = header;

    return status;
}

void
set_destroy (set_t * set)
{
    set_header_t *header;
    const iset_t *ds;

    header = *set;
    ds = interface (header->type);

    ds->destroy (&(header->set));
    free (header);
    *set = NULL;
}

#define call_set_interface_function(fun, s, ...)        \
    ({                                                  \
        set_header_t *header = s;                       \
        iset_t const *ds = interface(header->type);     \
        return ds->fun(header->set, ## __VA_ARGS__);    \
    })


unsigned int
set_length (const set_t set)
{
    call_set_interface_function (length, set);
}

bool
set_is_empty (const set_t set)
{
    call_set_interface_function (is_empty, set);
}

bool
set_member (set_t set, set_element_t e)
{
    call_set_interface_function (member, set, e);
}

int
set_insert (set_t set, set_element_t e)
{
    call_set_interface_function (insert, set, e);
}

int
set_delete (set_t set, set_element_t e)
{
    call_set_interface_function (delete, set, e);
}

void
set_clear (set_t set)
{
    call_set_interface_function (clear, set);
}

#define call_set_interface_function3(fun, a, b, c)                      \
    ({                                                                  \
        set_header_t *a_header = a;                                     \
        set_header_t *b_header = b;                                     \
        set_header_t *c_header = *c;                                     \
        iset_t const *ds = interface(c_header->type);                   \
        return ds->fun(a_header->set, b_header->set, &(c_header->set)); \
    })

int
set_union (const set_t a, const set_t b, set_t * c)
{
    call_set_interface_function3 (union_, a, b, c);
}

int
set_intersection (const set_t a, const set_t b, set_t * c)
{
    call_set_interface_function3 (intersection, a, b, c);
}

int
set_difference (const set_t a, const set_t b, set_t * c)
{
    call_set_interface_function3 (difference, a, b, c);
}

void
set_print (const set_t set)
{
    call_set_interface_function (print, set);
}
