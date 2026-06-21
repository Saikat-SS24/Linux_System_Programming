#ifndef MY_HEADER_H   
#define MY_HEADER_H   

#include <stdio.h>

static int callCount = 0;

void greet() {
    callCount++;
    printf("Greeting #%d: Hello from the header!\n", callCount);
}

#endif               