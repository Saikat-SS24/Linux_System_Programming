#include <iostream>

using namespace std;

int main()
{
    FILE *fp=nullptr;
/*
    fopen()
    fclose()
    fwrite(), fprintf
    fread, fscanf(), fgets()

    fseek() => move the fp one one address to another
    from one location to another location defined by bytes
    ftell() => will let you know the current location of the file ptr

*/
    char line[100]={'\0',};
    fp = fopen("output.txt", "r");

    if(fp == nullptr)
    {
        cout<<"Unable to open the file"<<endl;
        return EXIT_FAILURE;
    }
    cout<<"\nFile Opened Successfully"<<endl;

    
    //while(fgets(line,99,fp) != nullptr)  //EOF/eof
    //    cout<<line<<endl;

   /* while(fp){
        fscanf(fp,"%s",line);
        cout<<line<<endl;
        
        getchar();
        
    }*/

    int noofBytes = fread(line,1,200,fp);
    cout<<line<<endl;
    cout<<"\nBytes: "<<noofBytes<<endl;

    FILE *fp1 = fopen("output1.txt", "w");

    if(fp1 == nullptr)
    {
        cout<<"Unable to open the file"<<endl;
        return EXIT_FAILURE;
    }
    cout<<"\nFile Opened Successfully for writing"<<endl;

    noofBytes = fwrite(line,1,20,fp1);
    cout<<"\nBytes: "<<noofBytes<<endl;

    fclose(fp1);
    fclose(fp);

    return EXIT_SUCCESS;
}