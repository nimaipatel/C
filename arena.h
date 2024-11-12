#include <stdlib.h>

typedef struct M_Region M_Region;
struct M_Region {
    M_Region *next;
    size_t len;
    size_t cap;
};

