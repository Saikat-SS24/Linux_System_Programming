#include <stdio.h>
#include <limits.h>

/*
 * explore_types - Comprehensive data type exploration
 *
 * Demonstrates all basic data types, their sizes,
 * ranges, and common operations.
 */
void explore_types(void) {
    printf("╔════════════════════════════════════════════╗\n");
    printf("║     DATA TYPE EXPLORATION PROGRAM          ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    /* Character types */
    printf("--- CHARACTER TYPES ---\n");
    char c1 = 'A';
    char c2 = 65;  /* ASCII value of 'A' */
    printf("char c1 = 'A': %c (ASCII: %d)\n", c1, c1);
    printf("char c2 = 65: %c (ASCII: %d)\n", c2, c2);
    printf("sizeof(char) = %lu byte(s)\n", sizeof(char));
    printf("Range: %d to %d\n\n", CHAR_MIN, CHAR_MAX);
    
    /* Integer types */
    printf("--- INTEGER TYPES ---\n");
    int i = 42;
    printf("int i = %d\n", i);
    printf("sizeof(int) = %lu byte(s)\n", sizeof(int));
    printf("Range: %d to %d\n", INT_MIN, INT_MAX);
    printf("Hex: %x, Octal: %o\n\n", i, i);
    
    /* Unsigned */
    unsigned int ui = 4294967295U;
    printf("unsigned int ui = %u\n", ui);
    printf("sizeof(unsigned int) = %lu byte(s)\n", sizeof(unsigned int));
    printf("Range: 0 to %u\n\n", UINT_MAX);
    
    /* Floating point */
    printf("--- FLOATING POINT TYPES ---\n");
    float f = 3.14159f;
    double d = 3.141592653589793;
    printf("float f = %f (%.10f)\n", f, f);
    printf("sizeof(float) = %lu byte(s)\n", sizeof(float));
    printf("double d = %lf (%.15lf)\n", d, d);
    printf("sizeof(double) = %lu byte(s)\n", sizeof(double));
    printf("Scientific: %e, %e\n\n", f, d);
    
    /* Pointer */
    printf("--- POINTER TYPE ---\n");
    int *ptr = &i;
    printf("int *ptr = &i\n");
    printf("Address: %p\n", (void *)ptr);
    printf("Value: %d\n", *ptr);
    printf("sizeof(pointer) = %lu byte(s)\n\n", sizeof(ptr));
    
    /* Type casting demo */
    printf("--- TYPE CASTING ---\n");
    int num = 10;
    float result = (float)num / 3;
    printf("%d / 3 (with cast) = %f\n", num, result);
    printf("%d / 3 (without cast) = %d\n\n", num, num/3);
}

int main(void) {
    explore_types();
    return 0;
}