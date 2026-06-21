#include "common.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"argc: "<<argc<<endl;
    for(int i=0;i<argc;i++)
        cout<<argv[i]<<endl;
    if(argc != 4){
        cout<<"\nUseage: ./app startNum EndNum"<<endl;
        exit(EXIT_FAILURE);
    }
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    for(int i=start;i<=end;i++)
    {
        cout<<"\n====="<<i<<"'s Table=====\n";
        for(int j=1;j<=10;j++)
            cout<<i<<" * "<<j<<" = "<<(i*j)<<endl;
        cout<<"\n=========================\n";
    }

    cout<<"\nEnd\n";

    return 0;
}

