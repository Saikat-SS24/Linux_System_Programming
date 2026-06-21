#include "common.h"

using namespace std;


int main()
{
    //bidirectional operation
    int child2parent[2];
    int parent2child[2];

    pipe(child2parent);
    pipe(parent2child);

    cout<<"\nchild2parent [0]: "<<child2parent[0]<<endl;
    cout<<"\nchild2parent [1]: "<<child2parent[1]<<endl;
    cout<<"\nparent2child [0]: "<<parent2child[0]<<endl;
    cout<<"\nparent2child [1]: "<<parent2child[1]<<endl;


    if(fork() == 0)
    {
        //child process
        close(child2parent[0]);
        close(parent2child[1]); //close the write fd
        
        //cout<<"\nChild Process\n";
        char wbuf_c[100] = {'\0',};
        char rbuf_c[100] = {'\0',};
        memset(wbuf_c,'\0',sizeof(wbuf_c));
        memset(rbuf_c,'\0',sizeof(rbuf_c));

        read(parent2child[0],rbuf_c, sizeof(rbuf_c)-1);
        cout<<"[parent] "<<rbuf_c<<endl;
        
        //answer is produced
        strcpy(wbuf_c,"\nB Tech (AI/ML) Course\n");
        write(child2parent[1], wbuf_c, strlen(wbuf_c));

        close(child2parent[1]);
        close(parent2child[0]); //close the read fd
        
    }
    else
    {
        //parent process
        //cout<<"\nParent Process\n";
        close(parent2child[0]);
        close(child2parent[1]);
        
        char wbuf_p[100] = {'\0',};
        char rbuf_p[100] = {'\0',};
        memset(wbuf_p,'\0',sizeof(wbuf_p));
        memset(rbuf_p,'\0',sizeof(rbuf_p));

        strcpy(wbuf_p,"\nAfter 12th what you want to do?\n");
        //question is passed to the child
        write(parent2child[1],wbuf_p,strlen(wbuf_p));

        //read the answer back from the child
        read(child2parent[0], rbuf_p, sizeof(rbuf_p)-1);
        cout<<"[child] "<<rbuf_p<<endl;

        close(parent2child[1]);
        close(child2parent[0]);
        
    }

    return 0;
       
}