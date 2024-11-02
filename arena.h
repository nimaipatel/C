#include <stdlib.h>

typedef struct M_Region M_Region;
struct M_Region {
    M_Region *next;
    size_t len;
    size_t cap;
};

typedef struct M_Arena M_Arena;
struct M_Arena {
    M_Region *begin;
    M_Region *end;
};

void *
M_Arena_Alloc(M_Arena *arena, size_t size)
{
}