#include <bits/stdint-uintn.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "set/bit_vector.h"

/**
 * Private bit vector definition
 */
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
    _bv->bv = calloc(cuts, sizeof(uint64_t));
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

uint8_t bit_vector_length(const bit_vector_t bv) {
    _bit_vector_t *_bv = bv;
    uint8_t length = 0;

    for (int i = 0; i < _bv->cuts; i++) {
        uint64_t cut = _bv->bv[i];
        for (int j = 0; j < 64; j++) {
            length += (cut & (1UL << j)) ? 1 : 0;
        }
    }
    return length;
}

bool bit_vector_is_empty(const bit_vector_t bv) {
    _bit_vector_t *_bv = bv;

    for (int i = 0; i < _bv->cuts; i++) {
        uint64_t cut = _bv->bv[i];
        if (cut > 0) {
            return false;
        }
    }

    return true;
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

int8_t bit_vector_union(const bit_vector_t a, const bit_vector_t b, bit_vector_t *c) {
    bit_vector_clear(*c);
    _bit_vector_t *_a = a, *_b = b, *_c = *c;
    int N = min(_a->cuts, _b->cuts, _c->cuts);
    for (int i = 0; i < N; i++)
        _c->bv[i] = _a->bv[i] | _b->bv[i];
    return 0;
}

int8_t bit_vector_intersection(const bit_vector_t a, const bit_vector_t b, bit_vector_t *c) {
    bit_vector_clear(*c);
    _bit_vector_t *_a = a, *_b = b, *_c = *c;
    int N = min(_a->cuts, _b->cuts, _c->cuts);
    for (int i = 0; i < N; i++)
        _c->bv[i] = _a->bv[i] & _b->bv[i];
    return 0;
}

int8_t bit_vector_difference(const bit_vector_t a, const bit_vector_t b, bit_vector_t *c) {
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
