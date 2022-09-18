#include <stdlib.h>

#include "list/linked_list.h"

/**
 * Private list definition
 */
typedef struct node_t {
    struct node_t *next;
    linked_list_element_t elem;
} node_t;

typedef struct {
    node_t *first;
    unsigned int n;
} _linked_list_t;


int
linked_list_init (linked_list_t * llist)
{
    _linked_list_t *list;

    list = malloc (sizeof (_linked_list_t));
    if (list == NULL)
        return -1;

    list->first = NULL;
    list->n = 0;
    *llist = list;

    return 0;
}

inline unsigned int
linked_list_length (const linked_list_t llist)
{
    return ((_linked_list_t *) llist)->n;
}

inline bool
linked_list_is_empty (const linked_list_t llist)
{
    return ((_linked_list_t *) llist)->n == 0;
}

inline bool
linked_list_is_full (const linked_list_t llist)
{
    return false;
}

linked_list_element_t
linked_list_first (const linked_list_t llist)
{
    _linked_list_t *list;

    list = llist;
    return list->first->elem;
}

linked_list_element_t
linked_list_last (const linked_list_t llist)
{
    _linked_list_t *list;
    node_t *node;

    list = llist;
    node = list->first;

    while (node->next != NULL)
        node = node->next;

    return node->elem;
}

linked_list_element_t
linked_list_get (const linked_list_t llist, unsigned int n)
{
    _linked_list_t *list;
    node_t *node;

    list = llist;
    node = list->first;

    for (int i = 0; i < n; i++)
        node = node->next;

    return node->elem;
}

int
linked_list_insert (linked_list_t llist, unsigned int n,
                    linked_list_element_t elem)
{
    _linked_list_t *list;
    node_t *node, *new_node;

    list = llist;
    node = list->first;

    if (n > list->n)
        return -1;              /* can't insert in this position */

    if (node == NULL) {         /* fisrt node */
        node = malloc (sizeof (node_t));
        if (node == NULL)
            return -1;

        node->elem = elem;
        node->next = NULL;
        list->first = node;
    } else {
        for (int i = 0; i < (int) n - 1; i++)
            node = node->next;

        new_node = malloc (sizeof (node_t));
        if (new_node == NULL)
            return -1;

        new_node->elem = elem;
        if (n == 0) {
            new_node->next = node;
            list->first = new_node;
        } else {
            new_node->next = node->next;
            node->next = new_node;
        }
    }

    list->n++;
    return 0;
}

int
linked_list_append (linked_list_t llist, linked_list_element_t elem)
{
    if (linked_list_is_full (llist))
        return -1;
    return linked_list_insert (llist, linked_list_length (llist), elem);
}

int
linked_list_prepend (linked_list_t llist, linked_list_element_t elem)
{
    if (linked_list_is_empty (llist))
        return -1;
    return linked_list_insert (llist, 0, elem);
}

linked_list_element_t
linked_list_remove (linked_list_t llist, unsigned int n)
{
    _linked_list_t *list;
    node_t *node, *remove_node;
    linked_list_element_t removed;

    list = llist;
    node = list->first;

    if (n == 0) {
        remove_node = node;
        list->first = node->next;
    } else {
        for (int i = 0; i < n - 1; i++)
            node = node->next;
        remove_node = node->next;
        node->next = remove_node->next;
    }
    removed = remove_node->elem;
    free (remove_node);
    list->n--;

    if (list->n == 0)
        list->first = NULL;

    return removed;
}

void
linked_list_clear (linked_list_t llist)
{
    int length = linked_list_length (llist);

    for (int i = 0; i < length; i++)
        linked_list_remove (llist, 0);
}

int
linked_list_locate (const linked_list_t llist, linked_list_element_t elem,
                    int (*cmp) (linked_list_element_t a,
                                linked_list_element_t b))
{
    _linked_list_t *list;
    node_t *node;
    int index = 0;

    list = llist;
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
linked_list_destroy (linked_list_t * llist)
{
    _linked_list_t *list = *llist;

    linked_list_clear (llist);
    free (list);
    *llist = NULL;
}
