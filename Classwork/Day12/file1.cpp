/*

datatype arrayName[Capacity];

int arr[10];

float marks[10];
float avg[3]
float temprature[10];


int a[5] = {0};
int a1[5] = {0,};
char emp_name[50] = {'\0'};

access the elements of the array

index value
arr[0] => 0 indicates index value

indexing starts from 0
and end up till (Capacity or Size) -1



-1
1


BA = oth elements address => array starts from this address


BA + sizeof(datatype)*indexValue

int a[3] = {1,2,3};

a[0]=>1 => 2000
a[1]=>2 => 2004

BA + (sizeof(datatype)*indexValue)
2000 + sizeof(int)*0 = 2000+(4*-1) = 2000
2000 + sizeof(int)*1 = 2000+(4*1) = 2004
2000 + sizeof(int)*2 = 2000+(4*2) = 2008



*/

#include <iostream>

using namespace std;

int main()
{
    int arr[5]={10,20,30,40,50};

    printf("\nBase Address of the arr = %u\n",arr);
    printf("\nBase Address of the arr = %u\n",&arr[0]);

    for(int i=0;i<(sizeof(arr)/sizeof(arr[0]));i++)
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