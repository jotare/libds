#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include <inttypes.h>
#include <stdbool.h>

typedef void* static_queue_t;
typedef unsigned int static_queue_element_t;

/**
 * Initialize a static queue of `n` elements
 *
 * @return positive integer if success, -1 if operation fails
 */
int static_queue_init(static_queue_t *squeue, unsigned int n);

/**
 * Size
 */
unsigned int static_queue_length(const static_queue_t squeue);
bool static_queue_is_empty(const static_queue_t squeue);
bool static_queue_is_full(const static_queue_t squeue);

/**
 * Queue operations
 */
static_queue_element_t static_queue_front(const static_queue_t squeue);
int static_queue_enqueue(static_queue_t squeue, static_queue_element_t elem);
static_queue_element_t static_queue_dequeue(static_queue_t squeue);

void static_queue_clear(static_queue_t squeue);

/**
 * Destroy the `static_queue`. It must be called when the queue won't
 * be used anymore
 */
void static_queue_destroy(static_queue_t *squeue);

#endif /* STATIC_QUEUE_H */
