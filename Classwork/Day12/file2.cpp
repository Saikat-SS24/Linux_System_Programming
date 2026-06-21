#include <iostream>

using namespace std;

int main()
{
    int arr[5]={0,};//={10,20,30,40,50};

    printf("\nBase Address of the arr = %u\n",arr);
    printf("\nBase Address of the arr = %u\n",&arr[0]);

    for(int i=0;i<(sizeof(arr)/sizeof(arr[0]));i++)
        printf("\nAddress of the arr[%d] = %u\t Value = %d\n",i, &arr[i],arr[i]);
    
    for(int i=0;i<5;i++)
        scanf("%d",&arr[i]);

    for(int i=0;i<5;i++)
        printf("\nAddress of the arr[%d] = %u\t Value = %d\n",i, &arr[i],arr[i]);
    
    

    printf("\n\n");

    return 0;

    
}

/*
output:

Base Address of the arr = 2352449792

Base Address of the arr = 2352449792

Address of the arr[0] = 2352449792	 Value = 10

Address of the arr[1] = 2352449796	 Value = 20

Address of the arr[2] = 2352449800	 Value = 30

Address of the arr[3] = 2352449804	 Value = 40

Address of the arr[4] = 2352449808	 Value = 50



*/