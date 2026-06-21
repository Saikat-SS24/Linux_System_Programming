#include <iostream>
#include "calc.h"

int Calculator::add(int v1, int v2){ return v1 + v2; }
int Calculator::sub(int v1, int v2){ return v1 - v2; }
int Calculator::mul(int v1, int v2){ return v1 * v2; }
float Calculator::division(int v1, int v2){ 
    
    if (v2==0)
        throw std::runtime_error("Divide by Zero");
    return v1 / v2; 
}


/*

ar rcs lib<className/fileName>.a <className/fileName>.o

*/