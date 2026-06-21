#include <iostream>

using namespace std;

int main()
{
    int weight;
    cin >> weight;

    if (weight < 0)
    {
        cout << "Invalid Input" << endl;
    }
    else if (weight > 7000)
    {
        cout << "Overloaded" << endl;
    }
    else if (weight == 0)
    {
        cout << "Estimated time: 0 minutes" << endl;
    }
    else if  (weight <= 2000) 
    {
        cout << "Estimated time: 25 minutes" << endl;
    }
    else if (weight <= 4000)
    {
        cout << "Estimated time: 35 minutes" << endl;
    }
    else
    {
        cout << "Estimated time: 45 minutes" << endl;
    }

    return 0;
}