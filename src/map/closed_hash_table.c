#include <stdlib.h>

#include "map/closed_hash_table.h"

/**
 * Private closed hash table definition
 */

typedef enum { EMPTY, FILLED, DELETED } cell_state_t;

typedef struct {
    closed_hash_table_key_t key;
    closed_hash_table_value_t value;
    cell_state_t state;
} cell_t;

typedef struct {
    unsigned int size;
    cell_t *bucket_table;
} bucket_table_header_t;


static unsigned int
hash(closed_hash_table_key_t key, unsigned int bucket_table_size)
{
    return key % bucket_table_size;
}

static bool
same_key(closed_hash_table_key_t a, closed_hash_table_key_t b)
{
    return a == b;
}

static closed_hash_table_key_t
copy_key(closed_hash_table_key_t * key)
{
    return *key;
}

static closed_hash_table_value_t
copy_value(closed_hash_table_value_t * value)
{
    return *value;
}

static unsigned int
locate_key_or_empty(bucket_table_header_t * hash_table,
                    closed_hash_table_key_t key)
{
    unsigned int initial = hash(key, hash_table->size);
    unsigned int idx = initial;
    unsigned int count = 0;

    while ((count < hash_table->size)
           && !(hash_table->bucket_table[idx].state == FILLED
                && same_key(hash_table->bucket_table[idx].key, key))
           && (hash_table->bucket_table[idx].state != EMPTY)
        ) {
        count++;
        idx = (initial + count) % hash_table->size;
    }

    return idx;
}

static unsigned int
locate_key_or_empty_or_deleted(bucket_table_header_t * hash_table,
                               closed_hash_table_key_t key)
{
    unsigned int initial = hash(key, hash_table->size);
    unsigned int idx = initial;
    unsigned int count = 0;

    while ((count < hash_table->size)
           && !(hash_table->bucket_table[idx].state == FILLED
                && same_key(hash_table->bucket_table[idx].key, key))
           && (hash_table->bucket_table[idx].state != EMPTY)
           && (hash_table->bucket_table[idx].state != DELETED)
        ) {
        count++;
        idx = (initial + count) % hash_table->size;
    }

    return idx;
}


int
closed_hash_table_init(closed_hash_table_t * closed_hash_table,
                       unsigned int size)
{
    bucket_table_header_t *hash_table;
    cell_t *bucket_table;

    hash_table = malloc(sizeof(bucket_table_header_t));
    if (hash_table == NULL)
        return -1;

    bucket_table = malloc(sizeof(cell_t) * size);
    if (bucket_table == NULL) {
        free(hash_table);
        return -1;
    }

    hash_table->size = size;
    hash_table->bucket_table = bucket_table;
    for (int i = 0; i < size; i++) {
        hash_table->bucket_table[i].state = EMPTY;
    }

    *closed_hash_table = hash_table;
    return 0;
}

int
closed_hash_table_set(closed_hash_table_t closed_hash_table,
                      closed_hash_table_key_t key,
                      closed_hash_table_value_t value)
{
    bucket_table_header_t *hash_table = closed_hash_table;
    unsigned int idx = locate_key_or_empty(hash_table, key);

    if (same_key(hash_table->bucket_table[idx].key, key)) {
        /* found, overwrite value */
        hash_table->bucket_table[idx].value = copy_value(&value);
        return 0;
    }

    /* search an empty or deleted space */
    idx = locate_key_or_empty_or_deleted(hash_table, key);

    if (hash_table->bucket_table[idx].state == EMPTY
        || hash_table->bucket_table[idx].state == DELETED) {
        hash_table->bucket_table[idx].key = copy_key(&key);
        hash_table->bucket_table[idx].value = copy_value(&value);
        hash_table->bucket_table[idx].state = FILLED;
        return 0;
    }

    /* hash table is full */
    return -1;
}

int
closed_hash_table_get(const closed_hash_table_t closed_hash_table,
                      closed_hash_table_key_t key,
                      closed_hash_table_value_t * value)
{
    bucket_table_header_t *hash_table = closed_hash_table;
    unsigned int idx = locate_key_or_empty(hash_table, key);

    if (same_key(hash_table->bucket_table[idx].key, key)) {
        *value = copy_value(&(hash_table->bucket_table[idx].value));
        return 0;
    }

    return -1;
}

bool
closed_hash_table_contains(const closed_hash_table_t
                           closed_hash_table, closed_hash_table_key_t key)
{
    bucket_table_header_t *hash_table = closed_hash_table;
    unsigned int idx = locate_key_or_empty(hash_table, key);

    return same_key(hash_table->bucket_table[idx].key, key);
}

int
closed_hash_table_delete(closed_hash_table_t closed_hash_table,
                         closed_hash_table_key_t key)
{
    bucket_table_header_t *hash_table = closed_hash_table;
    unsigned int idx = locate_key_or_empty(hash_table, key);

    if (same_key(hash_table->bucket_table[idx].key, key)) {
        hash_table->bucket_table[idx].state = DELETED;
    }

    return 0;
}

void
closed_hash_table_destroy(closed_hash_table_t * closed_hash_table)
{
    bucket_table_header_t *hash_table = *closed_hash_table;

    free(hash_table->bucket_table);
    free(hash_table);
    *closed_hash_table = NULL;
}

#ifdef DEBUG
#include <stdio.h>

static void
print(bucket_table_header_t * hash_table)
{
    printf("\n");
    printf("HASH TABLE:\n");
    for (int i = 0; i < hash_table->size; i++) {
        printf("[%d] ", i);
        switch (hash_table->bucket_table[i].state) {
        case EMPTY:
            printf("EMPTY");
            break;
        case FILLED:
            printf("K(%c) = V(%d)",
                   hash_table->bucket_table[i].key,
                   hash_table->bucket_table[i].value);
            break;
        case DELETED:
            printf("DELETED");
        }
        printf("\n");
    }
}
#endif // DEBUG
