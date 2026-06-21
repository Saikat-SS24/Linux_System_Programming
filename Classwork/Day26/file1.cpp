#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <cerrno>

using namespace std;


int main()
{
    int fd = open("demo.txt", O_CREAT | O_WRONLY, 0644);

    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    cout<<"File opened successfully!"<<endl;

    write(fd,"hello", 5);

    close(fd);


    fd = open("demo.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    cout<<"fd value: "<<fd<<endl;

    char str1[100] = {'\0',};

    read(fd,str1,sizeof(str1)-1);

    cout<<str1<<endl;
    close(fd);

    fd = open("demo.txt", O_WRONLY | O_APPEND);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    cout<<"fd value: "<<fd<<endl;
    

    const char str2[] = "This is with append mode\n";
    
    write(fd,str2, strlen(str2));

    close(fd);


    fd = open("demo.txt", O_RDWR);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    
    int fd1 = dup(fd);

    const char str3[] = "This is with RDWR mode\n";
    
    lseek(fd1,5,SEEK_SET);
    write(fd1,str3, strlen(str3));


    lseek(fd1, 0, SEEK_SET); //move to the begning of the file
    off_t filesize = lseek(fd1,0,SEEK_END); //move to the end of file

    cout<<"\nFile Size: "<<filesize<<endl;


    //meta data of the file

    struct stat st;

    if(stat("demo.txt", &st) == 0)
    {
        //print info
        cout<<"Size: "<<st.st_size<<" bytes"<<endl;
        cout<<"Inode: "<<st.st_ino<<endl;
        if(S_ISREG(st.st_mode))
            cout<<"\nIts a regural file"<<endl;
    }
    else
        perror("stat");


    close(fd1);

 
    return 0;

}