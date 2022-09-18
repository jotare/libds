#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "set/linked_list_set.h"

/**
 * Private linked list set definition
 */
typedef struct node_t {
    struct node_t *next;
    linked_list_set_element_t elem;
} node_t;

typedef struct {
    node_t *first;
    unsigned int n;
} _linked_list_set_t;


int linked_list_set_init(linked_list_set_t *lls) {
    _linked_list_set_t *set;

    set = malloc(sizeof(_linked_list_set_t));
    if (set == NULL)
        return -1;

    set->first = NULL;
    set->n = 0;
    *lls = set;

    return 0;
}

unsigned int linked_list_set_length(const linked_list_set_t lls) {
    _linked_list_set_t *set = lls;

    return set->n;
}

bool linked_list_set_is_empty(const linked_list_set_t lls) {
    return linked_list_set_length(lls) == 0;
}

/** Find element `e` into a sorted linked list set */
bool linked_list_set_member(linked_list_set_t lls, linked_list_set_element_t e) {
    _linked_list_set_t *set = lls;
    node_t *ptr = set->first;

    while (ptr != NULL && ptr->elem <= e) {
        if (ptr->elem == e)
            return true;
        ptr = ptr->next;
    }
    return false;
}

/** Insert `e` into a sorted linked list set */
int linked_list_set_insert(linked_list_set_t lls, linked_list_set_element_t e) {
    _linked_list_set_t *set = lls;
    node_t *node = set->first;

    if (node == NULL) {         /* add first element into the set  */
        node_t *first_node = malloc(sizeof(node_t));
        if (first_node == NULL)
            return -1;

        first_node->elem = e;
        first_node->next = NULL;
        set->first = first_node;
        set->n++;

    } else {
        node_t *node_before = NULL;

        // search end of list or a greater element
        while (node != NULL && node->elem < e) {
            node_before = node;
            node = node->next;
        }

        if (node == NULL || node->elem > e) {
            node_t *new_node = malloc(sizeof(node_t));
            if (new_node == NULL)
                return -1;

            if (node_before == NULL) { // add at the beginning
                new_node->next = node;
                set->first = new_node;
            } else {            // add at the middle or end
                new_node->next = node_before->next;
                node_before->next = new_node;
            }

            new_node->elem = e;
            set->n++;
        }
    }

    return 0;
}

/** Find element `e` into a sorted linked list set and delete it. As
    the set is sorted, if an element greater than e is found, we can
    return safely */
int linked_list_set_delete(linked_list_set_t lls, linked_list_set_element_t e) {

    _linked_list_set_t *set = lls;
    node_t *node = set->first;

    // empty set
    if (node == NULL) {
        return 0;
    }

    node_t *node_before = NULL;

    while (node != NULL && node->elem < e) {
        node_before = node;
        node = node->next;
    }

    // element not found
    if (node == NULL || node->elem > e) {
        return 0;
    }

    if (node->elem == e && node_before == NULL) {
        set->first = node->next;
        free(node);
        set->n--;
    } else if (node->elem == e) {
        node_before->next = node->next;
        free(node);
        set->n--;
    }

    if (set->n == 0) {
        set->first = NULL;
    }

    return 0;
}

void linked_list_set_clear(linked_list_set_t lls) {
    _linked_list_set_t *set = lls;

    if (set->first == NULL)
        return;

    node_t *node = set->first;
    node_t *next = node->next;

    while (next != NULL) {
        free(node);
        node = next;
        next = next->next;
    }

    free(node);
    set->first = NULL;
    set->n = 0;
}

int linked_list_set_union(const linked_list_set_t lls_a, const linked_list_set_t lls_b, linked_list_set_t *lls_c) {
    linked_list_set_clear(*lls_c);

    _linked_list_set_t *a = lls_a;
    _linked_list_set_t *b = lls_b;

    node_t *a_ptr = a->first;
    node_t *b_ptr = b->first;

    while (a_ptr != NULL && b_ptr != NULL) {
        linked_list_set_element_t e;

        if (a_ptr->elem == b_ptr->elem) {
            e = a_ptr->elem;
            a_ptr = a_ptr->next;
            b_ptr = b_ptr->next;
        } else if (a_ptr->elem < b_ptr->elem) {
            e = a_ptr->elem;
            a_ptr = a_ptr->next;
        } else {
            e = b_ptr->elem;
            b_ptr = b_ptr->next;
        }

        linked_list_set_insert(*lls_c, e);
    }

    if (a_ptr != NULL && b_ptr == NULL) {
        while (a_ptr != NULL) {
            linked_list_set_insert(*lls_c, a_ptr->elem);
            a_ptr = a_ptr->next;
        }
    } else if (a_ptr == NULL && b_ptr != NULL) {
        while (b_ptr != NULL) {
            linked_list_set_insert(*lls_c, b_ptr->elem);
            b_ptr = b_ptr->next;
        }
    }

    return 0;
}

int linked_list_set_intersection(const linked_list_set_t lls_a, const linked_list_set_t lls_b, linked_list_set_t *lls_c) {
    linked_list_set_clear(*lls_c);

    _linked_list_set_t *a = lls_a;
    _linked_list_set_t *b = lls_b;

    node_t *a_ptr = a->first;
    node_t *b_ptr = b->first;

    while (a_ptr != NULL && b_ptr != NULL) {
        linked_list_set_element_t e;

        if (a_ptr->elem == b_ptr->elem) {
            e = a_ptr->elem;
            a_ptr = a_ptr->next;
            b_ptr = b_ptr->next;
            linked_list_set_insert(*lls_c, e);
        } else if (a_ptr->elem < b_ptr->elem) {
            a_ptr = a_ptr->next;
        } else {
            b_ptr = b_ptr->next;
        }

    }

    return 0;
}

int linked_list_set_difference(const linked_list_set_t lls_a, const linked_list_set_t lls_b, linked_list_set_t *lls_c) {
    linked_list_set_clear(*lls_c);

    _linked_list_set_t *a = lls_a;
    _linked_list_set_t *b = lls_b;

    node_t *a_ptr = a->first;
    node_t *b_ptr = b->first;

    while (a_ptr != NULL && b_ptr != NULL) {
        linked_list_set_element_t e;

        if (a_ptr->elem == b_ptr->elem) {
            e = a_ptr->elem;
            a_ptr = a_ptr->next;
            b_ptr = b_ptr->next;
        } else if (a_ptr->elem < b_ptr->elem) {
            e = a_ptr->elem;
            a_ptr = a_ptr->next;
            linked_list_set_insert(*lls_c, e);
        } else {
            e = b_ptr->elem;
            b_ptr = b_ptr->next;
        }

    }

    if (a_ptr == NULL && b_ptr != NULL) {
        while (a_ptr != NULL) {
            linked_list_set_insert(*lls_c, a_ptr->elem);
            a_ptr = a_ptr->next;
        }
    }

    return 0;
}

void linked_list_set_destroy(linked_list_set_t *lls) {
    _linked_list_set_t *set = *lls;

    linked_list_set_clear(*lls);
    free(set);
    *lls = NULL;
}

void linked_list_set_print(const linked_list_set_t llset) {
    _linked_list_set_t *set = llset;
    node_t *node = set->first;

    printf("Linked List Set { ");
    while (node != NULL) {
        printf("%d ", node->elem);
        node = node->next;
    }
    printf("}\n");
}
