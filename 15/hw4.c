#include <stdio.h>
#include <stdlib.h>

void print_hex(void * hex, int length);
void print_vars(unsigned int esp);

void recover ()
{
    int * x;
    // Find out where recover's stack is
    unsigned int pointer = (unsigned int)&x;
    // Offset bask to last foo's stack
    pointer += 0x20;
    pointer -= 0x0c;
    // Space that foos stack uses
    int foo_space = 0x40;
    // How many times we have to print
    int countDown = *(int *)(pointer + 0x4c);
    // Bring the stack pointer back to the first instance
    pointer += foo_space * countDown;
    // Print the first instance
    print_vars(pointer);
    // Loop down through the stack frames
    int i;
    for (i = 0; i < countDown; ++i)
    {
        pointer -= foo_space;
        print_vars(pointer);
    }
    return;
}

void print_vars(unsigned int esp)
{
    // Set some locals for clarity
    int a = *(int *)(esp + 0x40);
    short b = *(short *)(esp + 0x44);
    char c = *(char *)(esp + 0x48);
    // int countUp = *(int *)(esp + 0x4c);
    // int countDown = *(int *)(esp + 0x50);

    // Print
    printf("foo called with args\n");
    printf("  a: ");
    print_hex(&a, sizeof(a));
    printf("\n");

    printf("  b: ");
    print_hex(&b, sizeof(b));
    printf("\n");

    printf("  c: ");
    print_hex(&c, sizeof(c));
    printf("\n");

    // printf("    countUp:   %d\n", countUp);
    // printf("    countDown: %d\n", countDown);
    return;
}

void print_hex(void * hex, int length)
{
    int i;
    // Walk through the length given
    for (i = length - 1; i >= 0; --i)
    {
        unsigned char current = ((unsigned char *)hex)[i];
        // Divide by 16 to get the first four bytes
        char first = (current / 16);
        // Mod by 16 to get the first four bytes
        char second = (current % 16);
        // Do some ascci table magic
        if ( first <= 9 )
            first += 48;
        else
            first += 55;
        if ( second <= 9 )
            second += 48;
        else
            second += 55;
        // Put the chars into stdout
        putchar(first);
        putchar(second);
    }
    return;
}


/*
foo
    subl    $44, %esp
    movl    64(%esp), %ebx
    movl    68(%esp), %eax
    movl    72(%esp), %edx
    movl    80(%esp), %ecx
*/
