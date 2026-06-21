#include <iostream>
#include <limits>     // For numeric_limits
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

const char* FILE_NAME = "employees.bin";

struct EmployeeRecord {
    int id;
    char name[50];
    float salary;
    int is_active; 
};

// Logic for handling the input buffer 
void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class EmployeeFileHandler {
public:
    void initializeRecords() {
        int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Kernel Error: Could not create file");
            return;
        }

        for (int i = 0; i < 10; ++i) {
            EmployeeRecord emp;
            cout << "\n--- Record " << i + 1 << " ---" << endl;
            cout << "Enter ID: "; 
            while(!(cin >> emp.id)) { // Validate integer input
                cout << "Invalid ID. Enter a number: ";
                cin.clear();
                clearBuffer();
            }
            
            clearBuffer(); // Clear newline before getline
            cout << "Enter Name: "; 
            cin.getline(emp.name, 50);

            cout << "Enter Salary: "; 
            while(!(cin >> emp.salary)) {
                cout << "Invalid Salary. Enter a number: ";
                cin.clear();
                clearBuffer();
            }
            
            emp.is_active = 1;
            write(fd, &emp, sizeof(EmployeeRecord));
        }
        close(fd);
        cout << "\nAll 10 records are written ." << endl;
    }

    void updateSalary(int id, float newSalary) {
        int fd = open(FILE_NAME, O_RDWR);
        if (fd == -1) return;
        EmployeeRecord emp;
        while (read(fd, &emp, sizeof(EmployeeRecord)) > 0) {
            if (emp.id == id) {
                emp.salary = newSalary;
                lseek(fd, -sizeof(EmployeeRecord), SEEK_CUR);
                write(fd, &emp, sizeof(EmployeeRecord));
                cout << "Salary updated in binary file." << endl;
                close(fd);
                return;
            }
        }
        close(fd);
        cout << "ID not found." << endl;
    }
};

class User {
public:
    virtual void viewAll() = 0;
    virtual ~User() {}
};

class Manager : public User {
public:
    void viewAll() override {
        int fd = open(FILE_NAME, O_RDONLY);
        if (fd == -1) {
            cout << "Error: File doesn't exist. Admin must Insert records first." << endl;
            return;
        }
        EmployeeRecord emp;
        cout << "\n[MANAGER VIEW: ACTIVE STAFF]" << endl;
        while (read(fd, &emp, sizeof(EmployeeRecord)) > 0) {
            if (emp.is_active == 1) {
                cout << "ID: " << emp.id << " | Name: " << emp.name << " | Salary: " << emp.salary << endl;
            }
        }
        close(fd);
    }
};

class Admin : public User, public EmployeeFileHandler {
public:
    void viewAll() override {
        int fd = open(FILE_NAME, O_RDONLY);
        if (fd == -1) return;
        EmployeeRecord emp;
        cout << "\n[ADMIN VIEW: ALL RECORDS]" << endl;
        while (read(fd, &emp, sizeof(EmployeeRecord)) > 0) {
            cout << "ID: " << emp.id << " | Name: " << emp.name << " | Salary: " << emp.salary 
                 << (emp.is_active ? " [Active]" : " [LEFT]") << endl;
        }
        close(fd);
    }

    void markAsLeft(int id) {
        int fd = open(FILE_NAME, O_RDWR);
        if (fd == -1) return;
        EmployeeRecord emp;
        while (read(fd, &emp, sizeof(EmployeeRecord)) > 0) {
            if (emp.id == id) {
                emp.is_active = 0;
                lseek(fd, -sizeof(EmployeeRecord), SEEK_CUR);
                write(fd, &emp, sizeof(EmployeeRecord));
                cout << "Status updated to 'Left'." << endl;
                break;
            }
        }
        close(fd);
    }
};

int main() {
    int roleChoice;
    cout << "Login as: 1. Admin  2. Manager: ";
    cin >> roleChoice;

    if (roleChoice == 1) {
        Admin admin;
        int action;
        while(true) {
            cout << "\n1. Insert 10 Records\n2. View All\n3. Update Salary\n4. Mark Employee Left\n5. Exit\nChoice: ";
            cin >> action;
            if (action == 1) admin.initializeRecords();
            else if (action == 2) admin.viewAll();
            else if (action == 3) {
                int id; float sal;
                cout << "ID: "; cin >> id;
                cout << "New Salary: "; cin >> sal;
                admin.updateSalary(id, sal);
            }
            else if (action == 4) {
                int id; cout << "ID to mark left: "; cin >> id;
                admin.markAsLeft(id);
            }
            else break;
        }
    } else {
        Manager manager;
        manager.viewAll();
    }
    return 0;
}