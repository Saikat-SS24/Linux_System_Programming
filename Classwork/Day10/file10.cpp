#include <iostream>

using namespace std;


int main()
{
    char str1[200];
    char str2[200];
    
    //fgets(str1,198,stdin);
    scanf("%[^\n]s",str1);
    puts(str1);
    //puts(str2);

    return 0;
}