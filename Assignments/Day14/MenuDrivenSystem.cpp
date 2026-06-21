/* Create a menu driven program where each menu option is handled using a function pointer array */

#include <iostream>
using namespace std;

// 1. Define the menu functions
// All functions must have the same "signature" (return type and parameters)
void sayHello() {
    cout << "\n[Action] Hello! Hope you're having a great day." << endl;
}

void showDate() {
    cout << "\n[Action] Today is April 24, 2026." << endl;
}

void sayJoke() {
    cout << "\n[Action] Why do programmers prefer dark mode? Because light attracts bugs!" << endl;
}

int main() {
    // 2. Create the array of function pointers
    // Syntax: void (*arrayName[])()
    void (*menuActions[])() = { sayHello, showDate, sayJoke };

    int choice;
    int totalOptions = sizeof(menuActions) / sizeof(menuActions[0]);

    while (true) {
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1. Get a Greeting" << endl;
        cout << "2. Check the Date" << endl;
        cout << "3. Hear a Joke" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;
        }

        // 3. Use the choice to call the function from the array
        // We subtract 1 because array indices start at 0
        if (choice >= 1 && choice <= totalOptions) {
            menuActions[choice - 1](); 
        } else {
            cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}