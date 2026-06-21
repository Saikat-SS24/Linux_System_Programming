#include <iostream>
#define ROW 2
#define COL 4
using namespace std;


int main(void) {
    //const int ROW=2, COL=4;
    int arr[ROW][COL] = {1,2,3,4,5,6,7,8}; 

    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }
    cout<<"\n=====================\n";

    for(int i=0;i<ROW*COL;i++)
    {
            cout<<arr[0][i]<<" ";
        
    }
    cout<<endl;
    return 0;
}


/*

2d array

a[2][3] = 6*4 = 24 bytes
row1 = 2000 => 3*4bytes = 12 bytes
row2 = 3000 => 3*4bytes = 12 bytes

2000 - 2011 -> 12 bytes(row1) 2012-2023 bytes row2
DMA
*/