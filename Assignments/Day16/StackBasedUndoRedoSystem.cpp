/* Implement a text editor simulation using stacks:

- UNDO reverses last operation

- REDO reapplies undone operation

Use two stacks to manage operations
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

void displayState(stack<string> undoStack) {
    if (undoStack.empty()) {
        cout << "Current Text: [Empty]" << endl;
        return;
    }
    cout << "Current Text: " << undoStack.top() << endl;
}

int main() {
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText = "";
    int choice;

    while (true) {
        cout << "\n--- Text Editor Menu ---" << endl;
        displayState(undoStack);
        cout << "1. Type/Write Text" << endl;
        cout << "2. Undo" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string input;
            cout << "Enter text to add: ";
            cin.ignore(); // Clear buffer
            getline(cin, input);

            // Update current text state
            if (undoStack.empty()) currentText = input;
            else currentText = undoStack.top() + " " + input;

            undoStack.push(currentText);
            
            // New action clears the redo history
            while (!redoStack.empty()) redoStack.pop();

        } else if (choice == 2) {
            if (!undoStack.empty()) {
                string lastAction = undoStack.top();
                undoStack.pop();
                redoStack.push(lastAction);
                cout << "Action Undone." << endl;
            } else {
                cout << "Nothing to Undo!" << endl;
            }

        } else if (choice == 3) {
            if (!redoStack.empty()) {
                string restoredAction = redoStack.top();
                redoStack.pop();
                undoStack.push(restoredAction);
                cout << "Action Redone." << endl;
            } else {
                cout << "Nothing to Redo!" << endl;
            }

        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}