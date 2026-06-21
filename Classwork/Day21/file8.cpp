#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("test1.txt");
    
    if(!in)
    {
        cerr<<"\nUnbale to open the file\n";
        exit(EXIT_FAILURE);
    }

    string line="";

    while(getline(in,line))
        cout<<line<<endl;

    
    in.close();

    return 0;

}