#include <stdlib.h>

#include "list/doubly_linked_list.h"

/**
 * Private list definition
 */
typedef struct node_t {
    struct node_t *next;
    doubly_linked_list_element_t elem;
    struct node_t *prev;
} node_t;

typedef struct {
    node_t *first;
    node_t *last;
    unsigned int n;
} _doubly_linked_list_t;


int
doubly_linked_list_init (doubly_linked_list_t * dllist)
{
    _doubly_linked_list_t *list;

    list = malloc (sizeof (_doubly_linked_list_t));
    if (list == NULL)
        return -1;

    list->first = NULL;
    list->last = NULL;
    list->n = 0;
    *dllist = list;

    return 0;
}

inline unsigned int
doubly_linked_list_length (const doubly_linked_list_t dllist)
{
    return ((_doubly_linked_list_t *) dllist)->n;
}

inline bool
doubly_linked_list_is_empty (const doubly_linked_list_t dllist)
{
    return ((_doubly_linked_list_t *) dllist)->n == 0;
}

inline bool
doubly_linked_list_is_full (const doubly_linked_list_t dllist)
{
    return false;
}

doubly_linked_list_element_t
doubly_linked_list_first (const doubly_linked_list_t dllist)
{
    _doubly_linked_list_t *list;

    list = dllist;
    return list->first->elem;
}

doubly_linked_list_element_t
doubly_linked_list_last (const doubly_linked_list_t dllist)
{
    _doubly_linked_list_t *list;

    list = dllist;
    return list->last->elem;
}

doubly_linked_list_element_t
doubly_linked_list_get (const doubly_linked_list_t dllist, unsigned int n)
{
    _doubly_linked_list_t *list;
    node_t *node;
    int length;

    list = dllist;
    length = doubly_linked_list_length (dllist);

    if (n <= length / 2) {      /* forward search */
        node = list->first;
        for (int i = 0; i < n; i++)
            node = node->next;
    } else {                    /* backward search */
        node = list->last;
        for (int i = length - 1; i > n; i--)
            node = node->prev;
    }

    return node->elem;
}

int
doubly_linked_list_insert (doubly_linked_list_t dllist, unsigned int n,
                           doubly_linked_list_element_t elem)
{
    _doubly_linked_list_t *list;
    node_t *new_node;
    int length;

    list = dllist;

    if (n > list->n)
        return -1;              /* can't insert in this position */

    new_node = malloc (sizeof (node_t));
    if (new_node == NULL)
        return -1;
    new_node->elem = elem;
    length = doubly_linked_list_length (dllist);

    if (n == 0) {
        new_node->next = list->first;
        new_node->prev = NULL;

        list->first = new_node;
        if (length == 0)
            list->last = new_node;
        else
            new_node->next->prev = new_node;

    } else if (n == length) {
        new_node->next = NULL;
        new_node->prev = list->last;

        list->last = new_node;
        new_node->prev->next = new_node;

    } else {
        node_t *node;

        node = list->first;
        for (int i = 0; i < n - 1; i++)
            node = node->next;

        new_node->next = node->next;
        new_node->prev = node;

        new_node->prev->next = new_node;
        new_node->next->prev = new_node;
    }

    list->n++;
    return 0;
}

int
doubly_linked_list_append (doubly_linked_list_t dllist,
                           doubly_linked_list_element_t elem)
{
    if (doubly_linked_list_is_full (dllist))
        return -1;
    return doubly_linked_list_insert (dllist,
                                      doubly_linked_list_length (dllist),
                                      elem);
}

int
doubly_linked_list_prepend (doubly_linked_list_t dllist,
                            doubly_linked_list_element_t elem)
{
    if (doubly_linked_list_is_empty (dllist))
        return -1;
    return doubly_linked_list_insert (dllist, 0, elem);
}

doubly_linked_list_element_t
doubly_linked_list_remove (doubly_linked_list_t dllist, unsigned int n)
{
    _doubly_linked_list_t *list;
    node_t *remove_node;
    int length;
    doubly_linked_list_element_t removed;

    list = dllist;
    length = doubly_linked_list_length (dllist);

    if (n == 0) {
        remove_node = list->first;
        list->first = remove_node->next;

        if (length == 1)
            list->last = NULL;
        else
            remove_node->next->prev = NULL;

    } else if (n == length - 1) {
        remove_node = list->last;
        list->last = remove_node->prev;

        if (length == 1)
            list->first = NULL;
        else
            remove_node->prev->next = NULL;

    } else {
        node_t *node;

        node = list->first;
        for (int i = 0; i < n - 1; i++)
            node = node->next;

        remove_node = node;
        remove_node->prev->next = remove_node->next;
        remove_node->next->prev = remove_node->prev;
    }

    removed = remove_node->elem;
    free (remove_node);
    list->n--;

    return removed;
}

void
doubly_linked_list_clear (doubly_linked_list_t dllist)
{
    int length = doubly_linked_list_length (dllist);

    for (int i = 0; i < length; i++) {
        doubly_linked_list_remove (dllist, 0);
    }
}

int
doubly_linked_list_locate (const doubly_linked_list_t dllist,
                           doubly_linked_list_element_t elem,
                           int (*cmp) (doubly_linked_list_element_t a,
                                       doubly_linked_list_element_t b))
{
    _doubly_linked_list_t *list;
    node_t *node;
    int index = 0;

    list = dllist;
    node = list->first;

    if (node == NULL)
        return -1;

    while (node->next != NULL) {
        if (cmp (node->elem, elem) == 0)
            return index;
        index++;
        node = node->next;
    }

    return -1;
}

void
doubly_linked_list_destroy (doubly_linked_list_t * dllist)
{
    _doubly_linked_list_t *list;

    list = *dllist;

    doubly_linked_list_clear (*dllist);
    free (list);
    *dllist = NULL;
}
