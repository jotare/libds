#include <stdlib.h>

#include "queue/heap.h"
#include "queue/priority_queue.h"

typedef struct {
    priority_queue_type_t type;
    void *priority_queue;
} priority_queue_header_t;

typedef struct {
    int (*init)(priority_queue_t * pq, unsigned int size);
    int (*insert)(priority_queue_t pq, priority_queue_element_t element,
                  priority_queue_priority_t priority);
    int (*deletemin)(priority_queue_t pq, priority_queue_element_t * min);
    void (*destroy)(priority_queue_t * pq);
} ipriority_queue_t;

static const ipriority_queue_t heap = {
    heap_init,
    heap_insert,
    heap_deletemin,
    heap_destroy
};


static const ipriority_queue_t *
interface(priority_queue_type_t type)
{
    switch (type) {
    case DEFAULT_PRIORITY_QUEUE:
    case HEAP_PRIORITY_QUEUE:
    default:
        return &heap;
    }
}

int
priority_queue_init(priority_queue_t * priority_queue, unsigned int n,
                    priority_queue_type_t type)
{
    priority_queue_header_t *header;
    const ipriority_queue_t *ds = interface(type);

    header = malloc(sizeof(priority_queue_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init(&(header->priority_queue), n);

    if (status < 0)
        *priority_queue = NULL;
    else
        *priority_queue = header;

    return status;
}

void
priority_queue_destroy(priority_queue_t * priority_queue)
{
    priority_queue_header_t *header;
    const ipriority_queue_t *ds;

    header = *priority_queue;
    ds = interface(header->type);

    ds->destroy(&(header->priority_queue));
    free(header);
    *priority_queue = NULL;
}

#define call_priority_queue_interface_function(fun, q, ...)      \
    ({                                                  \
        priority_queue_header_t *header = q;                     \
        ipriority_queue_t const *ds = interface(header->type);   \
        return ds->fun(header->priority_queue, ## __VA_ARGS__);  \
    })

int
priority_queue_insert(priority_queue_t pq, priority_queue_element_t element,
                      priority_queue_priority_t priority)
{
    call_priority_queue_interface_function(insert, pq, element, priority);
}

int
priority_queue_deletemin(priority_queue_t pq, priority_queue_element_t * min)
{
    call_priority_queue_interface_function(deletemin, pq, min);
}
