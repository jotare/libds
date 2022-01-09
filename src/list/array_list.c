#include <stdlib.h>
#include <string.h>

#include "list/array_list.h"


/**
 * Private list definition
 */
typedef struct {
    array_list_element_t *l;
    uint8_t n;
    uint8_t max_length;
} _array_list_t;


/*
 * Public functions
 */
int8_t array_list_init(array_list_t *alist, uint8_t n) {
    _array_list_t *list;
    list = malloc(sizeof(_array_list_t));
    if (list == NULL)
	return -1;
    list->l = malloc(n*sizeof(array_list_element_t));
    if (list->l == NULL) {
	free(list);
	return -1;
    }
    list->n = 0;
    list->max_length = n;
    *alist = list;
    return 0;
}

uint8_t array_list_length(array_list_t alist) {
    return ((_array_list_t *)alist)->n;
}

bool array_list_is_empty(array_list_t alist) {
    _array_list_t *list;

    list = alist;
    return list->n == 0;
}

bool array_list_is_full(array_list_t alist) {
    _array_list_t *list;

    list = alist;
    return list->n == list->max_length;
}

array_list_element_t array_list_first(array_list_t alist) {
    _array_list_t *list;
    list = alist;

    return list->l[0];
}

array_list_element_t array_list_last(array_list_t alist) {
    _array_list_t *list;
    list = alist;

    return list->l[list->n-1];
}

array_list_element_t array_list_get(array_list_t alist, uint8_t n) {
    _array_list_t *list;

    list = alist;
    return list->l[n];
}

int8_t array_list_insert(array_list_t alist, uint8_t n, array_list_element_t elem) {
    _array_list_t *list;

    list = alist;
    
    if (list->n >= list->max_length)
	return -1;

    if (n > list->n)
        return -1;              /* can't insert in this position */

    memmove(list->l+n+1,
	    list->l+n,
	    (list->n-n)*sizeof(array_list_element_t));
    list->l[n] = elem;
    list->n++;
    return 0;
}

int8_t array_list_append(array_list_t alist, array_list_element_t elem) {
    if (array_list_is_full(alist))
	return -1;
    return array_list_insert(alist, array_list_length(alist), elem);
}

int8_t array_list_prepend(array_list_t alist, array_list_element_t elem) {
    if (array_list_is_full(alist))
	return -1;
    return array_list_insert(alist, 0, elem);
}

array_list_element_t array_list_remove(array_list_t alist, uint8_t n) {
    _array_list_t *list;
    array_list_element_t removed;

    list = alist;
    removed = list->l[n];
    memmove(list->l+n,
	    list->l+n+1,
	    (list->n-n-1)*sizeof(array_list_element_t));
    list->n--;
    return removed;
}

void array_list_clear(array_list_t alist) {
    _array_list_t *list;
    list = alist;

    list->n = 0;
}

int8_t array_list_locate(array_list_t alist, array_list_element_t elem,
			 int8_t(*cmp)(array_list_element_t a, array_list_element_t b)) {
    _array_list_t *list;
    list = alist;

    for (uint8_t i = 0; i < list->n; i++)
	if (cmp(list->l[i], elem) == 0)
	    return i;
    return -1;
}


void array_list_destroy(array_list_t *alist) {
    _array_list_t *list;
    list = *alist;
    free(list->l);
    free(list);
    *alist = NULL;
}
