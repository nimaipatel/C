#include <stdio.h>
#include <assert.h>

#ifndef FIFO_TYPE
#error FIFO_TYPE undefined...
#endif

#define TOKCAT_(a, b) a##b
#define TOKCAT(a, b) TOKCAT_(a, b)

#define Fifo(FIFO_TYPE) TOKCAT(Fifo_, FIFO_TYPE)
#define Fifo_Func(FIFO_TYPE, func) \
    TOKCAT(TOKCAT(TOKCAT(Fifo_, FIFO_TYPE), _), func)

typedef struct Fifo(FIFO_TYPE) Fifo(FIFO_TYPE);

void Fifo_Func(FIFO_TYPE, Push_Front)(Fifo(FIFO_TYPE *fifo), FIFO_TYPE item);
void Fifo_Func(FIFO_TYPE, Push_Back)(Fifo(FIFO_TYPE) * fifo, FIFO_TYPE item);
FIFO_TYPE Fifo_Func(FIFO_TYPE, Pop_Front)(Fifo(FIFO_TYPE) * fifo);

#define Fifo_Push_Front(FIFO_TYPE, v, i) Fifo_Func(FIFO_TYPE, Push_Front)(v, i)
#define Fifo_Push_Back(FIFO_TYPE, v, i) Fifo_Func(FIFO_TYPE, Push_Back)(v, i)
#define Fifo_Pop_Front(FIFO_TYPE, v) Fifo_Func(FIFO_TYPE, Pop_Front)(v)

#ifdef FIFO_IMPL

#define FIFO_MIN_SIZE 0x10

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Fifo(FIFO_TYPE) {
    FIFO_TYPE *items;
    size_t start;
    size_t len;
    size_t cap;
};

void
Fifo_Func(FIFO_TYPE, Grow)(Fifo(FIFO_TYPE) * fifo)
{
    if (fifo->len == fifo->cap) {
        size_t cap = MAX(FIFO_MIN_SIZE, fifo->cap * 2);
        FIFO_TYPE *items = malloc(sizeof(items[0]) * cap);

        for (size_t i = 0; i < fifo->len; i += 1) {
            items[i] = fifo->items[(fifo->start + i) % fifo->cap];
        }

        if (fifo->items) {
            free(fifo->items);
        }

        fifo->items = items;
        fifo->start = 0;
        fifo->cap = cap;
    }
}

void
Fifo_Func(FIFO_TYPE, Shrink)(Fifo(FIFO_TYPE) * fifo)
{
    if (fifo->len < fifo->cap / 4) {
        size_t cap = MAX(FIFO_MIN_SIZE, fifo->cap / 4);
        FIFO_TYPE *items = malloc(sizeof(items[0]) * cap);

        for (size_t i = 0; i < fifo->len; i += 1) {
            items[i] = fifo->items[(fifo->start + i) % fifo->cap];
        }

        if (fifo->items) {
            free(fifo->items);
        }

        fifo->items = items;
        fifo->start = 0;
        fifo->cap = cap;
    }
}

void
Fifo_Func(FIFO_TYPE, Push_Front)(Fifo(FIFO_TYPE) * fifo, FIFO_TYPE item)
{
    Fifo_Func(FIFO_TYPE, Grow)(fifo);
    fifo->start = (fifo->start - 1 + fifo->cap) % fifo->cap;
    fifo->items[fifo->start] = item;
    fifo->len += 1;
}

void
Fifo_Func(FIFO_TYPE, Push_Back)(Fifo(FIFO_TYPE) * fifo, FIFO_TYPE item)
{
    Fifo_Func(FIFO_TYPE, Grow)(fifo);
    fifo->items[(fifo->start + fifo->len) % fifo->cap] = item;
    fifo->len += 1;
}

FIFO_TYPE
Fifo_Func(FIFO_TYPE, Pop_Front)(Fifo(FIFO_TYPE) * fifo)
{
    assert(fifo->len > 0);

    FIFO_TYPE result = fifo->items[fifo->start];

    fifo->start += 1;
    fifo->start %= fifo->cap;
    fifo->len -= 1;

    Fifo_Func(FIFO_TYPE, Shrink)(fifo);

    return result;
}
#endif // FIFO_IMPL

#undef FIFO_TYPE
