/*
String functions

*/
#include <string.h> //include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char str1[20] = "amit";
    char str2[20] = "kumar";
    char str3[20] = "Amit";
    char str4[20] = {'\0',};
    char str5[20] = {'\0',};

    int len = strlen(str1);
    cout<<"\nLength of "<<str1<<" = "<<len<<endl;

    int ret = strcmp(str3,str1);
    cout<<"ret="<<ret<<endl;
    if(ret == 0)
        cout<<"Equal strings"<<endl;
    else if(ret > 0)
        cout<<"Str1 is greater than str2"<<endl;
    else
        cout<<"str1 is less than str2"<<endl;

	strcpy(str4, str2);
	cout<<"str4="<<str4<<endl;
    strcat(str4,str1);
    cout<<"str4="<<str4<<endl;

    strcpy(str5,str3);
    cout<<"str5="<<str5<<endl;
    strcat(str5, " ");
    cout<<"str5="<<str5<<endl;
    strcat(str5,str2);

    cout<<"str5="<<str5<<endl;


    char str6[20] = {'\0',};

    strcat(strcat(strcpy(str6,str3)," "),str2);
    cout<<"str6="<<str6<<endl;

    for(int i=0;i<strlen(str6);i++)
        printf("\n%c = %u",str6[i],&str6[i]);
    //use of strchr

    char *ptrStr=NULL;
    ptrStr = strchr(str6,'k');
    cout<<ptrStr<<endl;


    //very important part of code 
    //handling seg fault
    if(ptrStr != NULL)
        printf("\n%c = %u",*ptrStr, ptrStr);
    else
        printf("\nCharacter not found\n");
    cout<<endl;


    //use of strstr
    char *ptrStr2 = nullptr;
    ptrStr2 = strstr(str6, "kumar");
    if(ptrStr2 != NULL)
        printf("\nptrStr2\t%s = %u",ptrStr2, ptrStr2);
    else
        printf("\nSub String not found\n");
    cout<<endl;
    
    return 0;

}
