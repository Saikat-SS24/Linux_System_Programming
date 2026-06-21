/* Structs, Unions, Preprocessor directives
Task 1H: Use predefined macros in a printf and observe the output. Use these to write a logging macro, which when called logs the function name and line number in the log output. */

#include <cstdio>

int main() {
    printf("This is line %d in file %s, function %s\n", __LINE__, __FILE__, __func__);  
    printf("Next line is %d\n", __LINE__);  
    return 0;
}