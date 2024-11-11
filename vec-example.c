#define VEC_TYPE int
#define VEC_IMPL
#include "vec.h"

int
vec_example(void)
{
    Vec(int) v = { 0 };

    for (int i = 0; i < 10; i += 1) {
        Vec_Push(int, &v, i);
    }

    while (v.len > 0) {
        int i = Vec_Remove(int, &v, 0);
        printf("%d ", i);
    }

    printf("\n");

    return 0;
}
