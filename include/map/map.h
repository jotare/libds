/**
 * @file map.h
 * @brief Mapping ADT interface
 */
#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef void *map_t;
typedef char map_key_t;
typedef int map_value_t;

typedef enum { DEFAULT_MAP, OPEN_HASH_TABLE_MAP } map_type_t;

/**
 * Initialize and empty map. Size meaning is implementation dependent.
 */
int map_init(map_t * map, unsigned int size, map_type_t type);

/**
 * Set or overwrite `key` with `value` on the `map`
 */
int map_set(map_t map, map_key_t key, map_value_t value);

/**
 * Get an element from the map. Return 0 and set value if the map
 * contains key
 */
int map_get(const map_t map, map_key_t key, map_value_t * value);

/**
 * @return **true** if map has `key`.
 */
bool map_contains(const map_t map, map_key_t key);

/**
 * Delete a key from the map
 */
int map_delete(map_t map, map_key_t key);

/**
 * Destrpy the `map`. It must be called then the map won't be used
 * anymore.
 */
void map_destroy(map_t * map);

#endif /* MAP_H */
