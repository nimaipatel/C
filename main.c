#include "vec.h"
#include "heap.h"
#include <stdio.h>

int
cmp(int a, int b)
{
    return a - b;
}

VEC_IMPL(int)

HEAP_IMPL(int, cmp)

int
main(void)
{
    Vec(int) heap = { 0 };

    for (int i = 0; i <= 5; i += 1) {
        Vec_Push(int, &heap, i);
        Heap_Sift_Up(int, heap.items, heap.len, heap.len - 1);
    }

    for (int i = 9; i >= 5; i -= 1) {
        Vec_Push(int, &heap, i);
        Heap_Sift_Up(int, heap.items, heap.len, heap.len - 1);
    }

    while (heap.len > 0) {
        int min = Vec_Swap_Remove(int, &heap, 0);
        Heap_Sift_Down(int, heap.items, heap.len, 0);

        printf("%d\n", min);
    }

    Vec_Free(int, &heap);

    return 0;
}
