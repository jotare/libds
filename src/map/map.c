#include <stdlib.h>

#include "map/map.h"

typedef struct {
    map_type_t type;
    void *map;
} map_header_t;

typedef struct {
    int (*init)(map_t * map);
    int (*set)(map_t map, map_key_t key, map_value_t value);
    int (*get)(const map_t map, map_key_t key, map_value_t * value);
    bool (*contains)(const map_t map, map_key_t key);
    int (*delete)(map_t map, map_key_t key);
    void (*destroy)(map_t * map);
    void (*print)(const map_t map);
} imap_t;

static const imap_t *
interface(map_type_t type)
{
    switch (type) {
    case DEFAULT_MAP:
    default:
        return NULL;
    }
}

int
map_init(map_t * map, map_type_t type)
{
    map_header_t *header;
    const imap_t *ds = interface(type);

    header = malloc(sizeof(map_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init(&(header->map));

    if (status < 0)
        *map = NULL;
    else
        *map = header;

    return status;
}

void
map_destroy(map_t * map)
{
    map_header_t *header;
    const imap_t *ds;

    header = *map;
    ds = interface(header->type);

    ds->destroy(&(header->map));
    free(header);
    *map = NULL;
}

#define call_map_interface_function(fun, m, ...)        \
    ({                                                  \
        map_header_t *header = m;                       \
        imap_t const *ds = interface(header->type);     \
        return ds->fun(header->map, ## __VA_ARGS__);    \
    })

int
map_set(map_t map, map_key_t key, map_value_t value)
{
    call_map_interface_function(set, map, key, value);
}

int
map_get(const map_t map, map_key_t key, map_value_t * value)
{
    call_map_interface_function(get, map, key, value);
}

bool
map_contains(const map_t map, map_key_t key)
{
    call_map_interface_function(contains, map, key);
}

int
map_delete(map_t map, map_key_t key)
{
    call_map_interface_function(delete, map, key);
}

void
map_print(const map_t map)
{
    call_map_interface_function(print, map);
}
