#include <stdio.h>
#include <stdlib.h>

#define HEAP_IMPL(T, CMP) \
static inline void \
__Heap_##T##_Swap(T *a, T *b) \
{ \
    T x = *a; \
    T y = *b; \
 \
    *a = y; \
    *b = x; \
} \
 \
void \
__Heap_##T##_Sift_Up(T items[], size_t len, size_t index) \
{ \
    size_t parent = (index - 1) / 2; \
    while (index > 0 && CMP(items[parent], items[index]) > 0) { \
        __Heap_##T##_Swap(&items[parent], &items[index]); \
        index = parent; \
        parent = (index - 1) / 2; \
    } \
} \
 \
void \
__Heap_##T##_Sift_Down(T items[], size_t len, size_t index) \
{ \
    for (;;) { \
        const size_t left = 2 * index + 1; \
        const size_t right = left + 1; \
        size_t min_index = index; \
 \
        if (left < len && CMP(items[left], items[min_index]) < 0) { \
            min_index = left; \
        } \
 \
        if (right < len && CMP(items[right], items[min_index]) < 0) { \
            min_index = right; \
        } \
 \
        if (min_index == index) { \
            break; \
        } \
 \
        __Heap_##T##_Swap(&items[min_index], &items[index]); \
        index = min_index; \
    } \
} \


#define Sift_Up(T, items, len, index) __Heap_##T##_Sift_Up(items, len, index)
#define Sift_Down(T, items, len, index) __Heap_##T##_Sift_Down(items, len, index)
