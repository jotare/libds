/**
 * Private bit_vector definition
 */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "set/bit_vector.h"

typedef struct {
    uint64_t *bv;
    int cuts;
    int universe;
} _bit_vector_t;

int8_t bit_vector_init(bit_vector_t *bv, int n) {
    _bit_vector_t *_bv;
    _bv = malloc(sizeof(_bit_vector_t));
    if (_bv == NULL)
        return -1;

    int cuts = (n % 64 == 0) ? n / 64 : n / 64 + 1;
    _bv->bv = malloc(cuts*sizeof(uint64_t));
    if (_bv->bv == NULL) {
        free(_bv);
        return -1;
    }
    for (int i = 0; i < cuts; i++)
        _bv->bv[i] = 0;

    _bv->cuts = cuts;
    _bv->universe = n;
    *bv = _bv;
    return 0;
}

bool bit_vector_member(bit_vector_t bv, bit_vector_element_t e) {
    _bit_vector_t *_bv = bv;
    if (e > _bv->universe)
        return false;

    int cut = e / 64, idx = e % 64;
    uint64_t part = _bv->bv[cut];
    return part & (1UL << idx);
}

int8_t bit_vector_insert(bit_vector_t bv, bit_vector_element_t e) {
    _bit_vector_t *_bv = bv;
    if (e > _bv->universe)
        return -1;

    int cut = e / 64, idx = e % 64;
    uint64_t *part = &(_bv->bv[cut]);
    *part = *part | (1UL << idx);
    return 0;
}

int8_t bit_vector_delete(bit_vector_t bv, bit_vector_element_t e) {
    _bit_vector_t *_bv = bv;
    if (e > _bv->universe)
        return -1;

    int cut = e / 64, idx = e % 64;
    uint64_t *part = &(_bv->bv[cut]);
    *part = *part & ~(1UL << idx);
    return 0;
}

void bit_vector_clear(bit_vector_t bv) {
    _bit_vector_t *_bv = bv;

    for (int i = 0; i < _bv->cuts; i++)
        _bv->bv[i] = 0;
}

#define min2(a, b) ((a <= b) ? a : b)
#define min(a, b, c) min2(min2(a, b), c)

int8_t bit_vector_union(bit_vector_t a, bit_vector_t b, bit_vector_t *c) {
    bit_vector_clear(*c);
    _bit_vector_t *_a = a, *_b = b, *_c = *c;
    int N = min(_a->cuts, _b->cuts, _c->cuts);
    for (int i = 0; i < N; i++)
        _c->bv[i] = _a->bv[i] | _b->bv[i];
    return 0;
}

int8_t bit_vector_intersection(bit_vector_t a, bit_vector_t b, bit_vector_t *c) {
    bit_vector_clear(*c);
    _bit_vector_t *_a = a, *_b = b, *_c = *c;
    int N = min(_a->cuts, _b->cuts, _c->cuts);
    for (int i = 0; i < N; i++)
        _c->bv[i] = _a->bv[i] & _b->bv[i];
    return 0;
}

int8_t bit_vector_difference(bit_vector_t a, bit_vector_t b, bit_vector_t *c) {
    bit_vector_clear(*c);
    _bit_vector_t *_a = a, *_b = b, *_c = *c;
    int N = min(_a->cuts, _b->cuts, _c->cuts);
    for (int i = 0; i < N; i++)
        _c->bv[i] = _a->bv[i] & ~_b->bv[i];
    return 0;
}

void bit_vector_destroy(bit_vector_t *bv) {
    _bit_vector_t *_bv = *bv;

    free(_bv->bv);
    free(_bv);
    *bv = NULL;
}
