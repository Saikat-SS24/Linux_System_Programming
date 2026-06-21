/*Sort array of strings in ascending and descending order*/

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

bool compareAsc(string a, string b)
{
    return a < b;
}

bool compareDsc(string a, string b)
{
    return a > b;
}

int main()
{
    vector<string> names = {"Saikat", "Rajdeep", "Suman", "Deep"};
    sort(names.begin(), names.end(), compareAsc);
    
    cout << "Ascending: ";
    for(string s : names) cout << s << " ";
    cout << endl;

    sort(names.begin(), names.end(), compareDsc);

    cout << "Descending: ";
    for(string s : names) cout << s << " ";
    cout << endl;

    return 0;

}