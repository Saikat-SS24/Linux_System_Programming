/* 	
Task 11: STL Vectors	
Objective: Use STL vector to store integers and manipulate them.	
Steps:	
Create a vector<int> and populate it with some numbers.	
Write functions to find the sum and average of the numbers in the vector.	*/

#include <iostream>
#include <vector>
#include <numeric> // Required for accumulate

using namespace std;

// Function to calculate the sum of integers in a vector
int calculateSum(const vector<int>& nums) {
    int sum = 0;
    // Using a range-based for loop to iterate through the vector
    for (int n : nums) {
        sum += n;
    }
    return sum;
}

// Function to calculate the average
double calculateAverage(const vector<int>& nums) {
    if (nums.empty()) return 0.0; // Handle empty vector to avoid division by zero
    
    int sum = calculateSum(nums);
    return (double)sum / nums.size(); 
}

int main() {
    vector<int> numbers;
    
    // Adding numbers using push_back
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);

    // 2. Display the numbers
    cout << "Numbers in vector: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    // 3. Calculate and display Sum and Average
    int totalSum = calculateSum(numbers);
    double avg = calculateAverage(numbers);

    cout << "Sum: " << totalSum << endl;
    cout << "Average: " << avg << endl;

    return 0;
}