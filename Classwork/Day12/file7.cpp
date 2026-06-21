/* Variable arguments (advanced) */
#include <stdarg.h>
#include <iostream>

/* No parameters */
void say_hello(void) {
    printf("Hello!\n");
}

/* Single parameter */
void print_number(int n) {
    printf("Number: %d\n", n);
}

/* Multiple parameters */
int multiply(int a, int b) {
    return a * b;
}

int sum_all(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }
    
    va_end(args);
    return sum;
}

int main(void) {
    say_hello();
    print_number(42);
    
    int result = multiply(5, 6);
    printf("Result: %d\n", result);
    
    int total = sum_all(5, 10, 20, 30, 40,44);
    printf("Total: %d\n", total);
    
    return 0;
}