#include <stdlib.h>
#include <string.h>

#include "list/array_list.h"


/**
 * Private list definition
 */
typedef struct {
    array_list_element_t *l;
    unsigned int n;
    unsigned int max_length;
} _array_list_t;


/*
 * Public functions
 */
status_t
array_list_init(array_list_t * alist, unsigned int n)
{
    _array_list_t *list;

    list = malloc(sizeof(_array_list_t));
    if (list == NULL)
        return ALLOC_ERROR;

    list->l = calloc(n, sizeof(array_list_element_t));
    if (list->l == NULL) {
        free(list);
        return ALLOC_ERROR;
    }
    list->n = 0;
    list->max_length = n;
    *alist = list;
    return SUCCESS;
}

unsigned int
array_list_length(const array_list_t alist)
{
    return ((_array_list_t *) alist)->n;
}

bool
array_list_is_empty(const array_list_t alist)
{
    return ((_array_list_t *) alist)->n == 0;
}

bool
array_list_is_full(const array_list_t alist)
{
    _array_list_t *list;

    list = alist;
    return list->n == list->max_length;
}

array_list_element_t
array_list_first(const array_list_t alist)
{
    _array_list_t *list;

    list = alist;

    return list->l[0];
}

array_list_element_t
array_list_last(const array_list_t alist)
{
    _array_list_t *list;

    list = alist;

    return list->l[list->n - 1];
}

array_list_element_t
array_list_get(const array_list_t alist, unsigned int n)
{
    _array_list_t *list;

    list = alist;
    return list->l[n];
}

status_t
array_list_insert(array_list_t alist, unsigned int n,
                  array_list_element_t elem)
{
    _array_list_t *list;

    list = alist;

    if (list->n >= list->max_length)
        return FULL_ERROR;

    if (n > list->n)
        return INDEX_ERROR;     /* can't insert in this position */

    memmove(list->l + n + 1,
            list->l + n, (list->n - n) * sizeof(array_list_element_t));
    list->l[n] = elem;
    list->n++;
    return SUCCESS;
}

status_t
array_list_append(array_list_t alist, array_list_element_t elem)
{
    return array_list_insert(alist, array_list_length(alist), elem);
}

status_t
array_list_prepend(array_list_t alist, array_list_element_t elem)
{
    return array_list_insert(alist, 0, elem);
}

status_t
array_list_set(array_list_t alist, unsigned int n, array_list_element_t elem)
{
    _array_list_t *list;

    list = alist;
    if (n > list->n)
        return INDEX_ERROR;

    list->l[n] = elem;
    return SUCCESS;
}

array_list_element_t
array_list_remove(array_list_t alist, unsigned int n)
{
    _array_list_t *list;
    array_list_element_t removed;

    list = alist;
    /* TODO: add this condition */
    /* if (n > list->n) */
    /*     return INDEX_ERROR; */

    removed = list->l[n];
    memmove(list->l + n,
            list->l + n + 1,
            (list->n - n - 1) * sizeof(array_list_element_t));
    list->n--;
    return removed;
}

void
array_list_clear(array_list_t alist)
{
    _array_list_t *list;

    list = alist;

    list->n = 0;
}

int
array_list_locate(const array_list_t alist, array_list_element_t elem,
                  int (*cmp)(array_list_element_t a, array_list_element_t b))
{
    _array_list_t *list;

    list = alist;

    for (unsigned int i = 0; i < list->n; i++)
        if (cmp(list->l[i], elem) == 0)
            return i;
    return -1;
}


void
array_list_destroy(array_list_t * alist)
{
    _array_list_t *list;

    list = *alist;
    free(list->l);
    free(list);
    *alist = NULL;
}
