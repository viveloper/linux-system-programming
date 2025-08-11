#!/bin/bash

set -x

gcc -c main.c
gcc -c add.c
gcc main.o add.o -o a.out
