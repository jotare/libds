#include <stdlib.h>

#include "queue/dynamic_queue.h"

typedef struct node_t {
    struct node_t *next;
    dynamic_queue_element_t elem;
} node_t;

typedef struct {
    struct node_t *front, *rear;
    unsigned int n;
} _queue_t;

int
dynamic_queue_init (dynamic_queue_t * squeue)
{
    _queue_t *queue;

    queue = malloc (sizeof (_queue_t));
    if (queue == NULL)
        return -1;

    queue->front = NULL;
    queue->rear = NULL;
    queue->n = 0;
    *squeue = queue;

    return 0;
}

unsigned int
dynamic_queue_length (const dynamic_queue_t squeue)
{
    _queue_t *queue = squeue;

    return queue->n;
}

bool
dynamic_queue_is_empty (const dynamic_queue_t squeue)
{
    _queue_t *queue = squeue;

    return queue->n == 0;
}

bool
dynamic_queue_is_full (const dynamic_queue_t squeue)
{
    return false;
}

dynamic_queue_element_t
dynamic_queue_front (const dynamic_queue_t squeue)
{
    _queue_t *queue = squeue;

    return queue->front->elem;
}

int
dynamic_queue_enqueue (dynamic_queue_t squeue, dynamic_queue_element_t elem)
{
    _queue_t *queue = squeue;
    node_t *node;

    node = malloc (sizeof (node_t));
    if (node == NULL)
        return -1;

    node->elem = elem;
    node->next = NULL;

    if (queue->n == 0) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->n++;
    return 0;
}

dynamic_queue_element_t
dynamic_queue_dequeue (dynamic_queue_t squeue)
{
    _queue_t *queue = squeue;
    dynamic_queue_element_t elem;

    elem = queue->front->elem;

    if (queue->n == 1) {
        free (queue->front);
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        node_t *new_front;

        new_front = queue->front;
        queue->front = new_front->next;
    }
    queue->n--;
    return elem;
}

void
dynamic_queue_clear (dynamic_queue_t squeue)
{
    while (!dynamic_queue_is_empty (squeue))
        dynamic_queue_dequeue (squeue);
}

void
dynamic_queue_destroy (dynamic_queue_t * squeue)
{
    _queue_t *queue = *squeue;

    dynamic_queue_clear (*squeue);
    free (queue);
    *squeue = NULL;
}
