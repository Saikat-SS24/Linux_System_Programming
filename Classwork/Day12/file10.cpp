#include <iostream>
#define ROW 3
#define COL 3
using namespace std;

void display(int list2d[][COL],int);

int main()
{
    int list[ROW][COL]={1,2,3,4,5,6,7,8,9};

    display(list,ROW);

    return 0;
}


void display(int list2d[][COL], int count)
{
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<COL;j++)
            cout<<list2d[i][j]<<" ";
        cout<<endl;
        
    }
}
