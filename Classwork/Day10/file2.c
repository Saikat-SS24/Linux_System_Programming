#include <stdio.h>
#include <limits.h>  /* For type limits */
#include <float.h>   /* For float limits */

int main(void) {
    /* Integer types */
    char c = 'A';
    short s = 32000;
    int i = 1000000;
    long l = 2000000000L;
    long long ll = 9000000000000000000LL;
    
    /* Unsigned types */
    unsigned int ui = 4000000000U;
    
    /* Floating point */
    float f = 3.14159f;
    double d = 3.141592653589793;
    long double ld = 3.141592653589793238L;
    
    /* Boolean (C99+) */
   // _Bool flag = 1;  /* true */
    
    /* Display values */
    printf("char: %c (%d)\n", c, c);
    printf("short: %hd\n", s);
    printf("int: %d\n", i);
    printf("long: %ld\n", l);
    printf("long long: %lld\n", ll);
    printf("unsigned int: %u\n", ui);
    printf("float: %f\n", f);
    printf("double: %lf\n", d);
    printf("long double: %Lf\n", ld);
    //printf("boolean: %d\n", flag);
    
    /* Display sizes */
    printf("\n=== Data Type Sizes ===\n");
    printf("sizeof(char): %lu bytes\n", sizeof(char));
    printf("sizeof(short): %lu bytes\n", sizeof(short));
    printf("sizeof(int): %lu bytes\n", sizeof(int));
    printf("sizeof(long): %lu bytes\n", sizeof(long));
    printf("sizeof(long long): %lu bytes\n", sizeof(long long));
    printf("sizeof(float): %lu bytes\n", sizeof(float));
    printf("sizeof(double): %lu bytes\n", sizeof(double));
    
    /* Display ranges */
    printf("\n=== Data Type Ranges ===\n");
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("long: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("float: %e to %e\n", FLT_MIN, FLT_MAX);
    printf("double: %e to %e\n", DBL_MIN, DBL_MAX);
    
    return 0;
}
