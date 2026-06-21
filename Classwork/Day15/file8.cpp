#include <iostream>

using namespace std;

int main()
{
    FILE *fp1=nullptr;

    fp1 = fopen("output.txt", "r");

    if(fp1 == nullptr)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }
    char ch;
    int count=0;
    cout<<"file ptr is initially at "<<ftell(fp1)<<" position"<<endl;
    while((ch = fgetc(fp1))!=EOF){
        cout<<"\nfile ptr is now at "<<ftell(fp1)<<" position"<<endl;
        putc(ch,stdout);
        count++;
    }
    cout<<"No of chars read = "<<count<<endl;
    cout<<endl;
    return 0;
}