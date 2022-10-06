#include <stdlib.h>

#include "queue/heap.h"

typedef struct {
    heap_element_t element;
    heap_priority_t priority;
} node_t;

typedef struct {
    node_t *heap;
    unsigned int n;             /* number of elements */
    unsigned int size;
} _heap_t;

int
heap_init(heap_t * pq, unsigned int size)
{
    _heap_t *heap;

    heap = malloc(sizeof(_heap_t));
    if (heap == NULL)
        return -1;

    heap->heap = malloc(sizeof(node_t) * size);
    if (heap->heap == NULL) {
        free(heap);
        return -1;
    }
    heap->size = size;
    heap->n = 0;

    *pq = heap;

    return 0;
}

#define parent_idx(child_idx) (child_idx / 2)
#define left_child_idx(parent_idx) (parent_idx * 2)
#define right_child_idx(parent_idx) (parent_idx * 2 + 1)

#define parent(heap, idx) heap->heap[parent_idx(idx)]
#define left_child(heap, idx) heap->heap[left_child_idx(idx)]
#define right_child(heap, idx) heap->heap[right_child_idx(idx)]

static inline void
swap(_heap_t * heap, unsigned int i, unsigned int j)
{
    node_t tmp;

    tmp = heap->heap[i];
    heap->heap[i] = heap->heap[j];
    heap->heap[j] = tmp;
}

static inline void
swap_with_parent(_heap_t * heap, unsigned int idx)
{
    swap(heap, idx, parent_idx(idx));
}

static inline void
swap_with_left_child(_heap_t * heap, unsigned int idx)
{
    swap(heap, idx, left_child_idx(idx));
}

static inline void
swap_with_right_child(_heap_t * heap, unsigned int idx)
{
    swap(heap, idx, right_child_idx(idx));
}


int
heap_insert(heap_t pq, heap_element_t element, heap_priority_t priority)
{
    _heap_t *heap = pq;

    // heap is full
    if (heap->n >= heap->size)
        return -1;

    // insert element in the last position of the heap
    unsigned int idx = heap->n;

    heap->heap[idx].element = element;
    heap->heap[idx].priority = priority;

    // swap it with it's parents until we have a partial ordered tree again
    while (idx > 0 && parent(heap, idx).priority > priority) {
        swap_with_parent(heap, idx);
        idx = parent_idx(idx);
    }

    heap->n++;
    return 0;
}

int
heap_deletemin(heap_t pq, heap_element_t * min)
{
    _heap_t *heap = pq;

    if (heap->n == 0)
        return -1;

    *min = heap->heap[0].element;

    // put the last element in the root
    unsigned int idx = 0;

    heap->heap[idx] = heap->heap[heap->n - 1];

    heap->n--;

    // swap it with it's childs until we have a partial ordered tree again
    while (idx < heap->n / 2) {
        if (left_child(heap, idx).priority < right_child(heap, idx).priority) {
            swap_with_left_child(heap, idx);
            idx = left_child_idx(idx);
        } else {
            swap_with_right_child(heap, idx);
            idx = right_child_idx(idx);
        }
    }

    return 0;
}

void
heap_destroy(heap_t * pq)
{
    _heap_t *heap = *pq;

    free(heap->heap);
    free(heap);
    *pq = NULL;
}
