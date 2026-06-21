#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("test1.txt");
    
    if(!out)
    {
        cerr<<"\nUnbale to open the file\n";
        exit(EXIT_FAILURE);
    }

    out << "This is a test file uses file io stream\n";
    out<<"Hello World"<<endl;

    out.close();

    return 0;

}