/*

cmd line args

*/

#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    cout<<"\nNo of args passed: "<<argc<<endl;
    /*cout<<"\n0 arg: "<<argv[0]<<endl;
    cout<<"\n1 arg: "<<argv[1]<<endl;
    cout<<"\n2 arg: "<<argv[2]<<endl;
    cout<<"\n3 arg: "<<argv[3]<<endl;
    */

    for(int i=0;i<argc;i++)
        cout<<argv[i]<<endl;

    return 0;
}