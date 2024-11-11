#define FIFO_TYPE int
#define FIFO_IMPL
#include "fifo.h"

int
fifo_example(void)
{
    Fifo(int) q = { 0 };

    for (int i = 0; i < 10; i += 1) {
        Fifo_Push_Back(int, &q, i);
    }

    while (q.len > 0) {
        int i = Fifo_Pop_Front(int, &q);
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < 10; i += 1) {
        Fifo_Push_Front(int, &q, i);
    }

    while (q.len > 0) {
        int i = Fifo_Pop_Back(int, &q);
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
