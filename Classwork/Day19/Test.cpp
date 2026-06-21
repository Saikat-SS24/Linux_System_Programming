#include<iostream>
using namespace std;

class ArrayTest
{
    public:
        int data[100];
        int size;

        ArrayTest(int arr[], int n)
        {
            size = n;
            for(int i = 0; i < size; i++)
            {
                data[i] = arr[i];
            }
        }

        void findStats()
        {
            int max = data[0];
            int min = data[0];

            for(int i = 1; i < size; i++)
            {
                if (data[i] > max)
            }
        }
}