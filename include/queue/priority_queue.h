#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H


typedef void *priority_queue_t;
typedef int priority_queue_element_t;
typedef int priority_queue_priority_t;
typedef enum { DEFAULT_PRIORITY_QUEUE,
    HEAP_PRIORITY_QUEUE
} priority_queue_type_t;

int priority_queue_init(priority_queue_t * pq, unsigned int size,
                        priority_queue_type_t type);

int priority_queue_insert(priority_queue_t pq,
                          priority_queue_element_t element,
                          priority_queue_priority_t priority);

int priority_queue_deletemin(priority_queue_t pq,
                             priority_queue_element_t * min);

void priority_queue_destroy(priority_queue_t * pq);

#endif /* PRIORITY_QUEUE_H */
