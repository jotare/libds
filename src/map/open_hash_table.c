#include <stdlib.h>

#include "map/open_hash_table.h"

/**
 * Private open hash table definition
 */

typedef struct cell_t {
    open_hash_table_key_t key;
    open_hash_table_value_t value;
    struct cell_t *next;
} cell_t;

typedef struct {
    unsigned int size;
    cell_t **bucket_table;
} bucket_table_header_t;

/** Perform the hash(key) operation */
static unsigned int
hash(open_hash_table_key_t key, unsigned int bucket_table_size)
{
    return key % bucket_table_size;
}

static bool
same_key(open_hash_table_key_t a, open_hash_table_key_t b) {
    return a == b;
}

static open_hash_table_key_t
copy_key(open_hash_table_key_t *key) {
    return *key;
}

static open_hash_table_value_t
copy_value(open_hash_table_value_t *value) {
    return *value;
}


int
open_hash_table_init(open_hash_table_t * open_hash_table, unsigned int size)
{
    bucket_table_header_t *hash_table;

    hash_table = malloc(sizeof(bucket_table_header_t));
    if (hash_table == NULL)
        return -1;

    cell_t **bucket_table = malloc(sizeof(cell_t *) * size);
    if (bucket_table == NULL) {
        free(hash_table);
        return -1;
    }

    hash_table->bucket_table = bucket_table;
    hash_table->size = size;

    for (int i = 0; i < size; i++) {
        hash_table->bucket_table[i] = NULL;
    }

    *open_hash_table = hash_table;

    return 0;
}

int
open_hash_table_set(open_hash_table_t open_hash_table,
                    open_hash_table_key_t key, open_hash_table_value_t value)
{
    bucket_table_header_t *hash_table = open_hash_table;
    unsigned int bucket = hash(key, hash_table->size);
    cell_t *cell = hash_table->bucket_table[bucket];

    cell_t *element = malloc(sizeof(cell_t));

    if (element == NULL)
        return -1;

    if (cell == NULL) {
        hash_table->bucket_table[bucket] = element;
    } else {

        cell_t *cell_before = NULL;

        while (cell != NULL) {
            /* overwrite value and return */
            if (same_key(cell->key, key)) {
                cell->value = copy_value(&value);
                return 0;
            }

            cell_before = cell;
            cell = cell->next;
        }

        cell_before->next = element;
    }

    element->next = NULL;
    element->key = copy_key(&key);
    element->value = copy_value(&value);

    return 0;
}

int
open_hash_table_get(const open_hash_table_t open_hash_table,
                    open_hash_table_key_t key,
                    open_hash_table_value_t * value)
{
    bucket_table_header_t *hash_table = open_hash_table;
    unsigned int bucket = hash(key, hash_table->size);
    cell_t *cell = hash_table->bucket_table[bucket];

    if (cell == NULL)           /* empty bucket */
        return -1;

    while (cell != NULL) {
        if (same_key(cell->key, key)) {
            *value = copy_value(&cell->value);
            return 0;
        }
    }

    return -1;
}

bool
open_hash_table_contains(const open_hash_table_t
                         open_hash_table, open_hash_table_key_t key)
{
    bucket_table_header_t *hash_table = open_hash_table;
    unsigned int bucket = hash(key, hash_table->size);
    cell_t *cell = hash_table->bucket_table[bucket];

    if (cell == NULL)           /* empty bucket */
        return false;

    while (cell != NULL) {
        if (same_key(cell->key, key)) {
            return true;
        }
        cell = cell->next;
    }

    return false;
}

int
open_hash_table_delete(open_hash_table_t open_hash_table,
                       open_hash_table_key_t key)
{
    bucket_table_header_t *hash_table = open_hash_table;
    unsigned int bucket = hash(key, hash_table->size);
    cell_t *cell = hash_table->bucket_table[bucket];

    if (cell == NULL)           /* empty bucket */
        return 0;

    cell_t *cell_before = NULL;

    while (cell != NULL) {
        /* delete cell */
        if (same_key(cell->key, key)) {
            if (cell_before == NULL) {
                hash_table->bucket_table[bucket] = cell->next;
            } else {
                cell_before->next = cell->next;
            }
            free(cell);
            return 0;
        }

        cell_before = cell;
        cell = cell->next;
    }

    return 0;
}

void
open_hash_table_destroy(open_hash_table_t * open_hash_table)
{
    bucket_table_header_t *hash_table = *open_hash_table;

    for (int i = 0; i < hash_table->size; i++) {
        if (hash_table->bucket_table[i] != NULL) {
            cell_t *cell = hash_table->bucket_table[i];

            while (cell != NULL) {
                cell_t *next_cell = cell->next;

                free(cell);
                cell = next_cell;
            }

            hash_table->bucket_table[i] = NULL;
        }
    }
}
