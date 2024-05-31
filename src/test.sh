#!/bin/sh

gcc process.h process.c linkedlist.h linkedlist.c cpu.h cpu.c eval.h eval.c test.c
mv a.out test

