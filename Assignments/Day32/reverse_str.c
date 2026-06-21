#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

#define __NR_hello 454
#define __NR_reverse_string 455

int main()
{
    long ret;
    
    syscall(__NR_hello);
    
    char input[256];
    char output[256];
    
    printf("\nEnter string to be reversed: ");
    fgets(input,sizeof(input),stdin);
    
    input[strlen(input) -1] = '\0';
    
    size_t len = strlen(input);
    
    ret = syscall(__NR_reverse_string, input, output, len);
    
    if(ret < 0){
        printf("\nError: unable to reverse string\n");
        return 1;
    }
    
    printf("\nOriginal string: %s", input);
    printf("\nReversed string: %s\n", output);
    
    return 0;
}