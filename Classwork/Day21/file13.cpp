#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

int main()
{
    try{
    // string s = "hello";
    // cout<<s.at(100)<<endl;
    // long long *p = new long long[1000000000000LL];
    // delete []p;

    //char *name = NULL;
    //int num = atoi(name);
    string n = "10";
    int num = stoi("not_a_string");
    cout<<"num: "<<num<<endl;

    }
    catch(exception &e)
    {
        cerr<<"Exception: "<<e.what()<<endl;
    }
    return 0;
    

}