/* 	
Task 14: Range-based Loops	
Objective: Use a range-based loop to iterate over a container.	
Steps:	
Create an array or vector of integers.	
Iterate over the container using a range-based for loop and print each element.	 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 30, 40, 50};

    cout << "Vector elements: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    int scores[] = {95, 88, 72, 100};
    
    cout << "Array elements: ";
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}