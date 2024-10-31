#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (a > b) ? a : b

#define __VEC_MIN_SIZE 0x10

#define VEC_IMPL(T) \
typedef struct { \
    T *items; \
    size_t len; \
    size_t cap; \
} __Vec_##T; \
 \
void \
__Vec_##T##_Grow(__Vec_##T *vec) \
{ \
    if (vec->cap == vec->len) { \
        vec->cap = MAX(__VEC_MIN_SIZE, vec->cap * 2); \
        vec->items = realloc(vec->items, sizeof(vec->items[0]) * vec->cap); \
    } \
} \
 \
void \
__Vec_##T##_Shrink(__Vec_##T *vec) \
{ \
    if (vec->len < vec->cap / 4) { \
        vec->cap = MAX(__VEC_MIN_SIZE, vec->cap / 4); \
        vec->items = realloc(vec->items, sizeof(vec->items[0]) * vec->cap); \
    } \
} \
 \
size_t \
__Vec_##T##_Push(__Vec_##T *vec, T item) \
{ \
    __Vec_##T##_Grow(vec); \
    vec->items[vec->len++] = item; \
    return vec->len; \
} \
 \
T \
__Vec_##T##_Pop(__Vec_##T *vec) \
{ \
    T result = vec->items[--vec->len]; \
    __Vec_##T##_Shrink(vec); \
    return result; \
} \
 \
T \
__Vec_##T##_Swap_Remove(__Vec_##T *vec, size_t index) \
{ \
    T result = vec->items[index]; \
    vec->items[index] = vec->items[vec->len - 1]; \
    vec->len -= 1; \
    __Vec_##T##_Shrink(vec); \
    return result; \
} \
 \
T \
__Vec_##T##_Remove(__Vec_##T *vec, size_t index) \
{ \
    T result = vec->items[index]; \
    memmove(&vec->items[index], &vec->items[index + 1], vec->len - index); \
    vec->len -= 1; \
    __Vec_##T##_Shrink(vec); \
    return result; \
} \
void \
__Vec_##T##_Free(__Vec_##T *vec) \
{ \
    if (vec->items) { \
        free(vec->items); \
    } \
    *vec = (__Vec_##T){0}; \
}

#define Vec(T) __Vec_##T
#define Vec_Push(T, vec, item) __Vec_##T##_Push(vec, item)
#define Vec_Pop(T, vec) __Vec_##T##_Pop(vec)
#define Vec_Swap_Remove(T, vec, index) __Vec_##T##_Swap_Remove(vec, index)
#define Vec_Remove(T, vec, index) __Vec_##T##_Remove(vec, index)
#define Vec_Free(T, vec) __Vec_##T##_Free(vec)
