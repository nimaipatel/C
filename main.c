#include <stdio.h>

#include "arena.h"

#include "fifo-example.c"
#include "vec-example.c"

int
main(void)
{
    fifo_example();

    vec_example();

    return 0;
}

