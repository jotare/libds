#include <stdlib.h>

#include "set/bit_vector.h"
#include "set/set.h"

typedef struct {
    set_type_t type;
    void *set;
} set_header_t;

typedef struct {
    int8_t(*init)(set_t *set, int n);
    bool(*member)(set_t set, set_element_t e);
    int8_t(*insert)(set_t set, set_element_t e);
    int8_t(*delete)(set_t set, set_element_t e);
    void(*clear)(set_t set);
    int8_t(*union_)(const set_t a, const set_t b, set_t *c);
    int8_t(*intersection)(const set_t a, const set_t b, set_t *c);
    int8_t(*difference)(const set_t a, const set_t b, set_t *c);
    void(*destroy)(set_t *set);
} iset_t;

static const iset_t bit_vector = {
    bit_vector_init,
    bit_vector_member,
    bit_vector_insert,
    bit_vector_delete,
    bit_vector_clear,
    bit_vector_union,
    bit_vector_intersection,
    bit_vector_difference,
    bit_vector_destroy
};

static const iset_t *interface(set_type_t type) {
    switch (type) {
    case BIT_VECTOR_SET:
    case DEFAULT_SET:
    default:
        return &bit_vector;
    }
}

int8_t set_init(set_t *set, int n, set_type_t type) {
    set_header_t *header;
    const iset_t *ds = interface(type);

    header = malloc(sizeof(set_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int8_t status = ds->init(&(header->set), n);

    if (status < 0)
        *set = NULL;
    else
        *set = header;

    return status;
}

void set_destroy(set_t *set) {
    set_header_t *header;
    const iset_t *ds;

    header = *set;
    ds = interface(header->type);

    ds->destroy(&(header->set));
    free(header);
    *set = NULL;
}

#define call_set_interface_function(fun, s, ...)        \
    ({                                                  \
        set_header_t *header = s;                       \
        iset_t const *ds = interface(header->type);     \
        return ds->fun(header->set, ## __VA_ARGS__);    \
    })


bool set_member(set_t set, set_element_t e) {
    call_set_interface_function(member, set, e);
}

int8_t set_insert(set_t set, set_element_t e) {
    call_set_interface_function(insert, set, e);
}

int8_t set_delete(set_t set, set_element_t e) {
    call_set_interface_function(delete, set, e);
}

void set_clear(set_t set) {
    call_set_interface_function(clear, set);
}

#define call_set_interface_function3(fun, a, b, c)                      \
    ({                                                                  \
        set_header_t *a_header = a;                                     \
        set_header_t *b_header = b;                                     \
        set_header_t *c_header = *c;                                     \
        iset_t const *ds = interface(c_header->type);                   \
        return ds->fun(a_header->set, b_header->set, &(c_header->set)); \
    })

int8_t set_union(const set_t a, const set_t b, set_t *c) {
    call_set_interface_function3(union_, a, b, c);
}

int8_t set_intersection(const set_t a, const set_t b, set_t *c) {
    call_set_interface_function3(intersection, a, b, c);
}

int8_t set_difference(const set_t a, const set_t b, set_t *c) {
    call_set_interface_function3(difference, a, b, c);
}
