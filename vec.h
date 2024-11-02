#include <stdlib.h>
#include <string.h>

#ifndef VEC_TYPE
#error VEC_TYPE undefined...
#endif

#define TOKCAT_(a, b) a##b
#define TOKCAT(a, b) TOKCAT_(a, b)

#define Vec(VEC_TYPE) TOKCAT(Vec_, VEC_TYPE)
#define Vec_Func(VEC_TYPE, func) TOKCAT(TOKCAT(TOKCAT(Vec_, VEC_TYPE), _), func)

typedef struct Vec(VEC_TYPE) Vec(VEC_TYPE);

size_t Vec_Func(VEC_TYPE, Push)(Vec(VEC_TYPE) * vec, VEC_TYPE item);
VEC_TYPE Vec_Func(VEC_TYPE, Pop)(Vec(VEC_TYPE) * vec);
VEC_TYPE Vec_Func(VEC_TYPE, Swap_Remove)(Vec(VEC_TYPE) * vec, size_t index);
VEC_TYPE Vec_Func(VEC_TYPE, Remove)(Vec(VEC_TYPE) * vec, size_t index);
void Vec_Func(VEC_TYPE, Free)(Vec(VEC_TYPE) * vec);

#define Vec_Push(VEC_TYPE, v, i) Vec_Func(VEC_TYPE, Push)((v), (i))
#define Vec_Pop(VEC_TYPE, v) Vec_Func(VEC_TYPE, Pop)((v))
#define Vec_Swap_Remove(VEC_TYPE, v, i) \
    Vec_Func(VEC_TYPE, Swap_Remove)((v), (i))
#define Vec_Remove(VEC_TYPE, v, i) Vec_Func(VEC_TYPE, Remove)((v), (i))
#define Vec_Free(VEC_TYPE, v) Vec_Func(VEC_TYPE, Free)((v))

#ifdef VEC_IMPL

#define VEC_MIN_SIZE 0x10

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Vec(VEC_TYPE) {
    VEC_TYPE *items;
    size_t len;
    size_t cap;
};

void
Vec_Func(VEC_TYPE, Grow)(Vec(VEC_TYPE) * vec)
{
    if (vec->cap == vec->len) {
        vec->cap = MAX(VEC_MIN_SIZE, vec->cap * 2);
        vec->items = realloc(vec->items, sizeof(vec->items[0]) * vec->cap);
    }
}

void
Vec_Func(VEC_TYPE, Shrink)(Vec(VEC_TYPE) * vec)
{
    if (vec->len < vec->cap / 4) {
        vec->cap = MAX(VEC_MIN_SIZE, vec->cap / 4);
        vec->items = realloc(vec->items, sizeof(vec->items[0]) * vec->cap);
    }
}

size_t
Vec_Func(VEC_TYPE, Push)(Vec(VEC_TYPE) * vec, VEC_TYPE item)
{
    Vec_Func(VEC_TYPE, Grow)(vec);
    vec->items[vec->len++] = item;
    return vec->len;
}

VEC_TYPE
Vec_Func(VEC_TYPE, Pop)(Vec(VEC_TYPE) * vec)
{
    VEC_TYPE result = vec->items[--vec->len];
    Vec_Func(VEC_TYPE, Shrink)(vec);
    return result;
}

VEC_TYPE
Vec_Func(VEC_TYPE, Swap_Remove)(Vec(VEC_TYPE) * vec, size_t index)
{
    VEC_TYPE result = vec->items[index];
    vec->items[index] = vec->items[vec->len - 1];
    vec->len -= 1;
    Vec_Func(VEC_TYPE, Shrink)(vec);
    return result;
}

VEC_TYPE
Vec_Func(VEC_TYPE, Remove)(Vec(VEC_TYPE) * vec, size_t index)
{
    VEC_TYPE result = vec->items[index];
    memmove(&vec->items[index], &vec->items[index + 1],
            sizeof(VEC_TYPE) * (vec->len - index));
    vec->len -= 1;
    Vec_Func(VEC_TYPE, Shrink)(vec);
    return result;
}

void
Vec_Func(VEC_TYPE, Free)(Vec(VEC_TYPE) * vec)
{
    if (vec->items) {
        free(vec->items);
    }
    *vec = (Vec(VEC_TYPE)){ 0 };
}

#undef VEC_IMPL

#endif // VEC_IMPL

#undef VEC_TYPE
