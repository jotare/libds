#ifndef QUEUE_H
#define QUEUE_H

#include <inttypes.h>
#include <stdbool.h>

typedef void *queue_t;
typedef unsigned int queue_element_t;
typedef enum { DEFAULT_QUEUE, STATIC_QUEUE, DYNAMIC_QUEUE } queue_type_t;

/**
 * Initialize a queue of `n` elements
 *
 * @return positive integer if success, -1 if operation fails
 */
int queue_init (queue_t * queue, unsigned int n, queue_type_t type);

/**
 * Size
 */
unsigned int queue_length (const queue_t queue);
bool queue_is_empty (const queue_t queue);
bool queue_is_full (const queue_t queue);

/**
 * Queue operations
 */
queue_element_t queue_front (const queue_t queue);
int queue_enqueue (queue_t queue, queue_element_t elem);
queue_element_t queue_dequeue (queue_t queue);

void queue_clear (queue_t queue);

/**
 * Destroy the `queue`. It must be called when the queue won't
 * be used anymore
 */
void queue_destroy (queue_t * queue);


#endif /* QUEUE_H */
