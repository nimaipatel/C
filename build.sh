#!/bin/sh

set -xe

CC=cc
FLAGS=
DEV_FLAGS="-Wall -Wextra -Wpedantic -Werror\
 -Wconversion -Wdouble-promotion\
 -Wno-unused-parameter -Wno-unused-function\
 -fsanitize=address,undefined -fsanitize-trap\
 -g3 -O0"

$CC $FLAGS $DEV_FLAGS ./main.c -o ./main
