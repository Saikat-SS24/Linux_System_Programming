#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    FILE *fp1=nullptr;

    fp1 = fopen("output1.txt", "r+");

    if(fp1 == nullptr)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }
    char line[] = "Hello, World";
    int count=0;
    cout<<"file ptr is initially at "<<ftell(fp1)<<" position"<<endl;
    fseek(fp1,0,SEEK_END);
    cout<<"file ptr is now at "<<ftell(fp1)<<" position"<<endl;
    fwrite(line,strlen(line),1,fp1);
    
    fclose(fp1);
    cout<<endl;
    return 0;
}