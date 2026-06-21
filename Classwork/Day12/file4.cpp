#include <iostream>

using namespace std;


int main(void) {
    /* Declaration and initialization */
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    /* Partial initialization */
    int matrix2[3][4] = {
        {1, 2},
        {5},
        {9, 10, 11}
    };  // Rest initialized to 0
    int ROW=2, COL=4;
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
            printf("%u\n",arr[i]);
        
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