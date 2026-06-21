/*If the marks obtained by a student in five different subjects are input through the keyboard, find
out the aggregate marks and percentage marks obtained by the student. Assume that the maximum
marks that can be obtained by a student in each subject are 100*/

#include <iostream>
using namespace std;

int main() {
  
    float s1, s2, s3, s4, s5, aggregate, percentage;

    cout << "--- Enter marks for 5 subjects (out of 100 each) ---" << endl;
    
    cout << "Subject 1: "; cin >> s1;
    cout << "Subject 2: "; cin >> s2;
    cout << "Subject 3: "; cin >> s3;
    cout << "Subject 4: "; cin >> s4;
    cout << "Subject 5: "; cin >> s5;

    // 1. Calculate Aggregate (Total)
    aggregate = s1 + s2 + s3 + s4 + s5;

    // 2. Calculate Percentage
    // Formula: (Total Marks Obtained / Total Maximum Marks) * 100
    // Since each is out of 100, Total Max = 500
    percentage = (aggregate / 500.0) * 100;

    // 3. Display results
    cout << "\n--- Result Summary ---" << endl;
    cout << "Aggregate Marks: " << aggregate << " / 500" << endl;
    cout << "Percentage:      " << percentage << "%" << endl;

    return 0;
}
