/* 	
Task 8: Namespaces Introduction	
Objective: Demonstrate the use of namespaces.	
Steps:	
Define two namespaces with the same function name but different implementations.	
Call both functions in the main() demonstrating the use of namespaces.	*/

#include <iostream>

using namespace std;

// First Namespace
namespace English {
    void greet() {
        cout << "Hello!" << endl;
    }
}

// Second Namespace
namespace Spanish {
    void greet() {
        cout << "¡Hola!" << endl;
    }
}

int main() {
    cout << "Calling from English namespace: ";
    English::greet();

    cout << "Calling from Spanish namespace: ";
    Spanish::greet();

    using English::greet;
    cout << "\nAfter 'using English::greet', calling greet() directly: ";
    greet(); 

    return 0;
}