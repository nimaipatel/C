#define VEC_TYPE int
#define VEC_IMPL
#include "vec.h"

#define FIFO_TYPE int
#define FIFO_IMPL
#include "fifo.h"

#include <stdio.h>
#include "nice.c"

int
main(void)
{
    Fifo(int) q = { 0 };
    Vec(int) v = { 0 };

    for (int i = 0; i < 10; i += 1) {
        Fifo_Push_Back(int, &q, i);
        Vec_Push(int, &v, i);
    }

    while (q.len > 0) {
        int i = Fifo_Pop_Front(int, &q);
        printf("%d ", i);
    }
    printf("\n");

    while (v.len > 0) {
        int i = Vec_Remove(int, &v, 0);
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
