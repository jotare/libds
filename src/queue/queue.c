#include <stdlib.h>

#include "queue/static_queue.h"
#include "queue/dynamic_queue.h"
#include "queue/queue.h"

typedef struct {
    queue_type_t type;
    void *queue;
} queue_header_t;

typedef struct {
    int (*init) (queue_t * queue, unsigned int n);
    unsigned int (*length) (queue_t queue);
    bool (*is_empty) (queue_t queue);
    bool (*is_full) (queue_t queue);
      queue_element_t (*front) (queue_t queue);
    int (*enqueue) (queue_t queue, queue_element_t elem);
      queue_element_t (*dequeue) (queue_t queue);
    void (*clear) (queue_t queue);
    void (*destroy) (queue_t * queue);
} iqueue_t;

static const iqueue_t static_queue = {
    static_queue_init,
    static_queue_length,
    static_queue_is_empty,
    static_queue_is_full,
    static_queue_front,
    static_queue_enqueue,
    static_queue_dequeue,
    static_queue_clear,
    static_queue_destroy
};

int
_dynamic_queue_init (dynamic_queue_t * dqueue, unsigned int fake_n)
{
    return dynamic_queue_init (dqueue);
}

static const iqueue_t dynamic_queue = {
    _dynamic_queue_init,
    dynamic_queue_length,
    dynamic_queue_is_empty,
    dynamic_queue_is_full,
    dynamic_queue_front,
    dynamic_queue_enqueue,
    dynamic_queue_dequeue,
    dynamic_queue_clear,
    dynamic_queue_destroy
};


static const iqueue_t *
interface (queue_type_t type)
{
    switch (type) {
    case STATIC_QUEUE:
        return &static_queue;
    case DEFAULT_QUEUE:
    case DYNAMIC_QUEUE:
    default:
        return &dynamic_queue;
    }
}

int
queue_init (queue_t * queue, unsigned int n, queue_type_t type)
{
    queue_header_t *header;
    const iqueue_t *ds = interface (type);

    header = malloc (sizeof (queue_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init (&(header->queue), n);

    if (status < 0)
        *queue = NULL;
    else
        *queue = header;

    return status;
}

void
queue_destroy (queue_t * queue)
{
    queue_header_t *header;
    const iqueue_t *ds;

    header = *queue;
    ds = interface (header->type);

    ds->destroy (&(header->queue));
    free (header);
    *queue = NULL;
}

#define call_queue_interface_function(fun, q, ...)      \
    ({                                                  \
        queue_header_t *header = q;                     \
        iqueue_t const *ds = interface(header->type);   \
        return ds->fun(header->queue, ## __VA_ARGS__);  \
    })


unsigned int
queue_length (queue_t queue)
{
    call_queue_interface_function (length, queue);
}

bool
queue_is_empty (queue_t queue)
{
    call_queue_interface_function (is_empty, queue);
}

bool
queue_is_full (queue_t queue)
{
    call_queue_interface_function (is_full, queue);
}

queue_element_t
queue_front (queue_t queue)
{
    call_queue_interface_function (front, queue);
}

int
queue_enqueue (queue_t queue, queue_element_t elem)
{
    call_queue_interface_function (enqueue, queue, elem);
}

queue_element_t
queue_dequeue (queue_t queue)
{
    call_queue_interface_function (dequeue, queue);
}

void
queue_clear (queue_t queue)
{
    call_queue_interface_function (clear, queue);
}
