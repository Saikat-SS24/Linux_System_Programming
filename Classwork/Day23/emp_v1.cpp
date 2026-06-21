#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Employee
{
private:
    int empId;
    string empName;
    double empSalary;
public:
    Employee(int id, string n, double s)
    : empId(id), empName(n), empSalary(s){}

    int getId() const { return empId; }
    string getName() const { return empName;}
    double getSal() const { return empSalary; }

    void display() const{
        cout<<"\nEmployee Details are\n";
        cout<<"ID: "<<empId<<endl;
        cout<<"Name: "<<empName<<endl;
        cout<<"Salary: "<<empSalary<<endl;
    }
};


//add employee
void addEmployee(vector<Employee>& emplist)
{
    int id;
    string name;
    double salary;

    cout<<"\nEnter ID Name Salary: ";
    cin>>id>>name>>salary;

    emplist.emplace_back(id,name,salary);
    cout<<"\nEmployee added successfully"<<endl;
}

void displayEmployees(const vector<Employee>&emplist)
{
    if(emplist.empty()){
        cout<<"\nNo Employee Records are available"<<endl;
        return;
    }

    for(const auto &emp : emplist)
        emp.display();
}

//search employee
void searchEmployee(const vector<Employee>&emplist, int id)
{
    for(const auto&emp : emplist)
    {
        if(emp.getId() == id)
        {
            cout<<"\nEmployee found"<<endl;
            return;
        }
    }

    cout<<"\nEmployee not found"<<endl;

}

//delete Employee
void deleteEmployee(vector<Employee>&emplist, int id)
{
    auto it =remove_if(emplist.begin(), emplist.end(),
                    [id](const Employee&e) {
                        return e.getId() == id;
                    });
    
    if(it != emplist.end()){
        emplist.erase(it,emplist.end());
        cout<<"\nEmployee deleted"<<endl;
    }
    else
        cout<<"\nEmployee not found"<<endl;

}


//sort by ID
void sortByID(vector<Employee>&emplist)
{
    sort(emplist.begin(), emplist.end(),
    [](const Employee& a, const Employee &b)
    {
        return a.getId() < b.getId();
    }
    );
    cout<<"\nSorting Done by ID!"<<endl;
}

//sort by name
void sortByName(vector<Employee>&emplist)
{
    sort(emplist.begin(), emplist.end(),
    [](const Employee& a, const Employee &b)
    {
        return a.getName() < b.getName();
    }
    );
    cout<<"\nSorting Done by Name!"<<endl;
}



void showMenu()
{
    cout<<"\n==========Employee Managemnet System==========\n";
    cout<<"\n1. Add Employee";
    cout<<"\n2. Display Employees";
    cout<<"\n3. Search Employee";
    cout<<"\n4. Delete Employee";
    cout<<"\n5. Sort Employee by IDs";
    cout<<"\n6. Sort Employee by Name";
    cout<<"\n0. Exit";
    cout<<"\nChoice: ";
    
}

int main()
{
    vector <Employee> emplist;
    int choice, id;

    while(true)
    {
        showMenu();
        cin>>choice;

        switch(choice)
        {
            case 0:
                cout<<"\nExiting the app..."<<endl;
                exit(EXIT_SUCCESS);
                break;
            case 1:
                addEmployee(emplist);
                break;
            case 2:
                displayEmployees(emplist);
                break;
            case 3:
                cout<<"\nEnter ID to search: ";
                cin>>id;
                searchEmployee(emplist,id);
                break;
            case 4:
                cout<<"\nEnter ID to delete: ";
                cin>>id;
                deleteEmployee(emplist,id);
                break;
            case 5:
                sortByID(emplist);
                break;
            case 6:
                sortByName(emplist);
                break;
            default:
                cout<<"\nInvalid Choice"<<endl;
        }
    }

    return 0;
}