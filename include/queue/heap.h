#ifndef HEAP_H
#define HEAP_H

typedef void *heap_t;
typedef int heap_element_t;
typedef int heap_priority_t;

int heap_init(heap_t * pq, unsigned int size);

int heap_insert(heap_t pq, heap_element_t element, heap_priority_t priority);

int heap_deletemin(heap_t pq, heap_element_t * min);

void heap_destroy(heap_t * pq);


#endif /* HEAP_H */
