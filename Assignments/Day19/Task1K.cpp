/* Task 1K: Use #pragma pack directive with a structure and observe the data layout in memory using gdb. */

#include <iostream>
using namespace std; 

struct StandardStruct {
    char a;     
    int b;      
    char c;     
};

#pragma pack(push, 1) 
struct PackedStruct {
    char a;     
    int b;      
    char c;     
};
#pragma pack(pop)    

int main() {
    StandardStruct s1 = {'A', 100, 'Z'};
    PackedStruct s2 = {'A', 100, 'Z'};

    std::cout << "Size of Standard: " << sizeof(s1) << " bytes" << std::endl;
    std::cout << "Size of Packed:   " << sizeof(s2) << " bytes" << std::endl;

    return 0; 
}