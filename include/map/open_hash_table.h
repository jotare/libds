#ifndef OPEN_HASH_TABLE_H
#define OPEN_HASH_TABLE_H

#include <stdbool.h>

typedef void *open_hash_table_t;
typedef char open_hash_table_key_t;
typedef int open_hash_table_value_t;

/**
 * Initialize and empty open_hash_table. Set `size` to the approximate number
 * of elements the hash table will contain to achieve O(1) operations. This
 * hash table can grow and shrink dynamically.
 */
int open_hash_table_init(open_hash_table_t * open_hash_table,
                         unsigned int size);

/**
 * Set or overwrite `key` with `value` on the `open_hash_table`
 */
int open_hash_table_set(open_hash_table_t open_hash_table,
                        open_hash_table_key_t key,
                        open_hash_table_value_t value);

/**
 * Get an element from the open_hash_table. Return 0 and set value if the
 * open_hash_table contains key
 */
int open_hash_table_get(const open_hash_table_t open_hash_table,
                        open_hash_table_key_t key,
                        open_hash_table_value_t * value);

/**
 * @return **true** if open_hash_table has `key`.
 */
bool open_hash_table_contains(const open_hash_table_t
                              open_hash_table, open_hash_table_key_t key);

/**
 * Delete a key from the open_hash_table
 */
int open_hash_table_delete(open_hash_table_t open_hash_table,
                           open_hash_table_key_t key);

/**
 * Destroy the `open_hash_table`. It must be called then the open_hash_table won't be used
 * anymore.
 */
void open_hash_table_destroy(open_hash_table_t * open_hash_table);

#endif /* OPEN_HASH_TABLE_H */
