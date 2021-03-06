#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include <inttypes.h>
#include <stdbool.h>

typedef void* static_queue_t;
typedef uint8_t static_queue_element_t;

/**
 * Initialize a static queue of `n` elements
 *
 * @return positive integer if success, -1 if operation fails
 */
int8_t static_queue_init(static_queue_t *squeue, uint8_t n);

/**
 * Size
 */
uint8_t static_queue_length(static_queue_t squeue);
bool static_queue_is_empty(static_queue_t squeue);
bool static_queue_is_full(static_queue_t squeue);

/**
 * Queue operations
 */
static_queue_element_t static_queue_front(static_queue_t squeue);
int8_t static_queue_enqueue(static_queue_t squeue, static_queue_element_t elem);
static_queue_element_t static_queue_dequeue(static_queue_t squeue);

void static_queue_clear(static_queue_t squeue);

/**
 * Destroy the `static_queue`. It must be called when the queue won't
 * be used anymore
 */
void static_queue_destroy(static_queue_t *squeue);

#endif /* STATIC_QUEUE_H */
