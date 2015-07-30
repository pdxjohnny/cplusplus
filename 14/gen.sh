#!/bin/bash

rm "headers.h" "source.c" all.c
cat *.h > "headers.h"
cat *.c > "source.c"
cat "headers.h" "source.c" > all.c
rm "headers.h" "source.c"
sed -i '/include "/d' ./all.c
gcc -Wall -O1 -m32 all.c -o hw5
