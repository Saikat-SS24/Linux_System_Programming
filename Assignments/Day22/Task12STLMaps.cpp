/* 
Task 12: STL Maps
Objective: Map students' names to their grades using an STL map.
Steps:
Create an std::map from string to char representing names and grades.
Insert some data into the map and print the contents. */

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    // 1. Create a map: Key = string (name), Value = char (grade)
    map<string, char> studentGrades;
    
    studentGrades["Alice"] = 'A';
    studentGrades["Charlie"] = 'C';
    
    studentGrades.insert(pair<string, char>("Bob", 'B'));

    studentGrades.emplace("David", 'B');

    // 3. Print the contents
    // Maps store data as 'pair' objects: .first is the key, .second is the value
    cout << "--- Student Grade Report ---" << endl;
    for (auto const& [name, grade] : studentGrades) {
        cout << "Student: " << name << " | Grade: " << grade << endl;
    }

    // 4. Accessing a specific grade
    string searchName = "Alice";
    if (studentGrades.count(searchName)) {
        cout << "\n" << searchName << "'s grade is: " << studentGrades[searchName] << endl;
    }

    return 0;
}