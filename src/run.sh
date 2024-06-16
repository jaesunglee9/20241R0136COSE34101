#!/bin/sh

gcc -Wall -Wextra -pedantic -g process.h process.c linkedlist.h linkedlist.c queue.h queue.c cpu.h cpu.c eval.h eval.c main.c -lm
mv a.out run
