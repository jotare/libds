#include <stdlib.h>

#include "queue/static_queue.h"

/**
 * Circular array implementation of a queue
 */

typedef struct {
    static_queue_element_t *queue;
    static_queue_element_t *front;
    static_queue_element_t *rear;
    uint8_t size;
} _queue_t;

int8_t static_queue_init(static_queue_t *squeue, uint8_t n) {
    _queue_t *queue;

    queue = malloc(sizeof(_queue_t));
    if (queue == NULL)
	return -1;

    queue->queue = calloc(n+1, sizeof(static_queue_element_t));
    if (queue->queue == NULL) {
	free(queue);
	return -1;
    }

    queue->front = queue->queue;
    queue->rear = queue->queue;
    queue->size = n+1;
    *squeue = queue;

    return 0;
}

uint8_t static_queue_length(static_queue_t squeue) {
    _queue_t *queue = squeue;

    if (queue->front == queue->rear)
	return 0;
    else if (queue->rear > queue->front)
	return queue->rear - queue->front;
    else
	return queue->size - (queue->front - queue->rear);
}

bool static_queue_is_empty(static_queue_t squeue) {
    _queue_t *queue = squeue;
    return queue->front == queue->rear;
}

bool static_queue_is_full(static_queue_t squeue) {
    _queue_t *queue = squeue;
    return ((queue->rear + 1) == queue->front) ||		\
	((queue->front + queue->size-1) == queue->rear);
}

static_queue_element_t static_queue_front(static_queue_t squeue) {
    _queue_t *queue = squeue;

    if (queue->front + 1 == queue->queue + queue->size)
	return *(queue->queue);
    else
	return *(queue->front);
}

int8_t static_queue_enqueue(static_queue_t squeue, static_queue_element_t elem) {
    _queue_t *queue = squeue;

    *queue->rear = elem;

    if (queue->rear + 1 == queue->queue + queue->size)
	queue->rear = queue->queue;
    else
	queue->rear++;

    return 0;
}

static_queue_element_t static_queue_dequeue(static_queue_t squeue) {
    _queue_t *queue = squeue;
    static_queue_element_t elem;

    elem = *queue->front;

    if (queue->front + 1 == queue->queue + queue->size)
	queue->front = queue->queue;
    else
	queue->front++;

    return elem;
}

void static_queue_clear(static_queue_t squeue) {
    while (!static_queue_is_empty(squeue))
	static_queue_dequeue(squeue);
}

void static_queue_destroy(static_queue_t *squeue) {
    _queue_t *queue = *squeue;
    free(queue->queue);
    free(queue);
    *squeue = NULL;
}
