#!/bin.bash

gcc -Wall -g -O1 -m32 -S hw4main.c
gcc -Wall -g -O1 -m32 -S hw4.c
gcc -m32 -g hw4main.s hw4.s -o hw4

