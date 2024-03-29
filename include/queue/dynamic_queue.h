#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *dynamic_queue_t;
typedef unsigned int dynamic_queue_element_t;

/**
 * Initialize a dynamic queue 
 *
 * @return positive integer if success, -1 if operation fails
 */
int dynamic_queue_init(dynamic_queue_t * squeue);

/**
 * Size
 */
unsigned int dynamic_queue_length(const dynamic_queue_t squeue);
bool dynamic_queue_is_empty(const dynamic_queue_t squeue);
bool dynamic_queue_is_full(const dynamic_queue_t squeue);

/**
 * Queue operations
 */
dynamic_queue_element_t dynamic_queue_front(const dynamic_queue_t squeue);
int dynamic_queue_enqueue(dynamic_queue_t squeue,
                          dynamic_queue_element_t elem);
dynamic_queue_element_t dynamic_queue_dequeue(dynamic_queue_t squeue);

void dynamic_queue_clear(dynamic_queue_t squeue);

/**
 * Destroy the `dynamic_queue`. It must be called when the queue won't
 * be used anymore
 */
void dynamic_queue_destroy(dynamic_queue_t * squeue);

#endif /* DYNAMIC_QUEUE_H */
