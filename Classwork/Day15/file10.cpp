#include <iostream>
#include <cstring>

using namespace std;

typedef struct book
{
    int id;
    char title[20];
}BOOK;


void getDetails(BOOK *b)
{
    cout<<"\nEnter the details of the book"<<endl;
    cout<<"\nID: ";cin>>b->id;
    cout<<"\nTitle: ";cin>>b->title;
}

void printDetails(BOOK b)
{
    cout<<"\n==============\n";
    cout<<"\ndetails of the book"<<endl;
    cout<<"\nID: "<<b.id;
    cout<<"\nTitle: "<<b.title;
    cout<<"\n==============\n";
}


int main()
{
    FILE *fp = nullptr;
    BOOK b[3];
    int ret=0;

    fp = fopen("store.db", "wb");

    for(int i=0;i<3;i++)
        getDetails(&b[i]);
    
    ret = fwrite(b,sizeof(BOOK),3,fp);
    if(ret == 0)
    {
        perror("fwrite");
        fclose(fp);
        return EXIT_FAILURE;
    }

    cout<<ret <<" bytes written on the file"<<endl;


    /*for(int i=0;i<3;i++)
        printDetails(b[i]);
    */
    fclose(fp);
    return 0;
}