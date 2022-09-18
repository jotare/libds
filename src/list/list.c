#include <stdlib.h>

#include "list/array_list.h"
#include "list/linked_list.h"
#include "list/doubly_linked_list.h"
#include "list/list.h"

typedef struct {
    list_type_t type;
    void *list;
} list_header_t;

typedef struct {
    int (*init) (list_t * list, unsigned int n);
    unsigned int (*length) (const list_t list);
    bool (*is_empty) (const list_t list);
    bool (*is_full) (const list_t list);
      list_element_t (*first) (const list_t list);
      list_element_t (*last) (const list_t list);
      list_element_t (*get) (const list_t list, unsigned int n);
    int (*insert) (list_t list, unsigned int n, list_element_t elem);
    int (*append) (list_t list, list_element_t elem);
    int (*prepend) (list_t list, list_element_t elem);
      list_element_t (*remove) (list_t list, unsigned int n);
    void (*clear) (list_t list);
    int (*locate) (const list_t list, list_element_t elem,
                   int (*cmp) (list_element_t a, list_element_t b));
    void (*destroy) (list_t * list);
} ilist_t;


static const ilist_t array_list = {
    array_list_init,
    array_list_length,
    array_list_is_empty,
    array_list_is_full,
    array_list_first,
    array_list_last,
    array_list_get,
    array_list_insert,
    array_list_append,
    array_list_prepend,
    array_list_remove,
    array_list_clear,
    array_list_locate,
    array_list_destroy
};

static int
_linked_list_init (linked_list_t * llist, unsigned int fake_n)
{
    return linked_list_init (llist);
}

static const ilist_t linked_list = {
    _linked_list_init,
    linked_list_length,
    linked_list_is_empty,
    linked_list_is_full,
    linked_list_first,
    linked_list_last,
    linked_list_get,
    linked_list_insert,
    linked_list_append,
    linked_list_prepend,
    linked_list_remove,
    linked_list_clear,
    linked_list_locate,
    linked_list_destroy
};

static int
_doubly_linked_list_init (doubly_linked_list_t * dlist, unsigned int fake_n)
{
    return doubly_linked_list_init (dlist);
}

static const ilist_t doubly_linked_list = {
    _doubly_linked_list_init,
    doubly_linked_list_length,
    doubly_linked_list_is_empty,
    doubly_linked_list_is_full,
    doubly_linked_list_first,
    doubly_linked_list_last,
    doubly_linked_list_get,
    doubly_linked_list_insert,
    doubly_linked_list_append,
    doubly_linked_list_prepend,
    doubly_linked_list_remove,
    doubly_linked_list_clear,
    doubly_linked_list_locate,
    doubly_linked_list_destroy
};


static const ilist_t *
interface (list_type_t type)
{
    switch (type) {
    case ARRAY_LIST:
        return &array_list;

    case DOUBLY_LINKED_LIST:
        return &doubly_linked_list;

    case DEFAULT_LIST:
    case LINKED_LIST:
    default:
        return &linked_list;
    }
}


int
list_init (list_t * list, unsigned int n, list_type_t type)
{
    list_header_t *header;
    const ilist_t *ds = interface (type);

    header = malloc (sizeof (list_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init (&(header->list), n);

    if (status < 0)
        *list = NULL;
    else
        *list = header;

    return status;
}

void
list_destroy (list_t * list)
{
    list_header_t *header;
    const ilist_t *ds;

    header = *list;
    ds = interface (header->type);

    ds->destroy (&(header->list));
    free (header);
    *list = NULL;
}

#define call_list_interface_function(fun, l, ...)                       \
    ({                                                                  \
        list_header_t *header = l;                                      \
        ilist_t const *ds = interface(header->type);                    \
        return ds->fun(header->list, ## __VA_ARGS__);                   \
    })


unsigned int
list_length (const list_t list)
{
    call_list_interface_function (length, list);
}

bool
list_is_empty (const list_t list)
{
    call_list_interface_function (is_empty, list);
}

bool
list_is_full (const list_t list)
{
    call_list_interface_function (is_full, list);
}

list_element_t
list_first (const list_t list)
{
    call_list_interface_function (first, list);
}

list_element_t
list_last (const list_t list)
{
    call_list_interface_function (last, list);
}

list_element_t
list_get (const list_t list, unsigned int n)
{
    call_list_interface_function (get, list, n);
}

int
list_insert (list_t list, unsigned int n, list_element_t elem)
{
    call_list_interface_function (insert, list, n, elem);
}

int
list_append (list_t list, list_element_t elem)
{
    call_list_interface_function (append, list, elem);
}

int
list_prepend (list_t list, list_element_t elem)
{
    call_list_interface_function (prepend, list, elem);
}

list_element_t
list_remove (list_t list, unsigned int n)
{
    call_list_interface_function (remove, list, n);
}

void
list_clear (list_t list)
{
    call_list_interface_function (clear, list);
}

int
list_locate (const list_t list, list_element_t elem,
             int (*cmp) (list_element_t a, list_element_t b))
{
    call_list_interface_function (locate, list, elem, cmp);
}
