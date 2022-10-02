#ifndef CLOSED_HASH_TABLE_H
#define CLOSED_HASH_TABLE_H

#include <stdbool.h>

typedef void *closed_hash_table_t;
typedef char closed_hash_table_key_t;
typedef int closed_hash_table_value_t;

/**
 * Initialize and empty closed_hash_table. `size` is the maximum
 * number of elements in a hash table
 */
int closed_hash_table_init(closed_hash_table_t * closed_hash_table,
                           unsigned int size);

/**
 * Set or overwrite `key` with `value` on the `closed_hash_table`
 */
int closed_hash_table_set(closed_hash_table_t closed_hash_table,
                          closed_hash_table_key_t key,
                          closed_hash_table_value_t value);

/**
 * Get an element from the closed_hash_table. Return 0 and set value if the
 * closed_hash_table contains key
 */
int closed_hash_table_get(const closed_hash_table_t closed_hash_table,
                          closed_hash_table_key_t key,
                          closed_hash_table_value_t * value);

/**
 * @return **true** if closed_hash_table has `key`.
 */
bool closed_hash_table_contains(const closed_hash_table_t
                                closed_hash_table,
                                closed_hash_table_key_t key);

/**
 * Delete a key from the closed_hash_table
 */
int closed_hash_table_delete(closed_hash_table_t closed_hash_table,
                             closed_hash_table_key_t key);

/**
 * Destroy the `closed_hash_table`. It must be called then the
 * closed_hash_table won't be used anymore.
 */
void closed_hash_table_destroy(closed_hash_table_t * closed_hash_table);

#endif /* CLOSED_HASH_TABLE_H */
