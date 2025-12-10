#include "types.h" // defines types like uint
#include "stat.h"  // contains file system initializations
#include "user.h"  // system call stubs for user
#include "fcntl.h" // file control definitions 


int main(int argc, char* argv[])
{

    if(argc != 3)
    {

        printf(2,"Usage: cp src dst");
        exit();
    }

    int src = open(argv[1],0);

    if(src<0)
    {

        printf(2,"cp: cannot open %s\n",argv[1]);
        exit();

    }

    int dst = open(argv[2], O_CREATE|O_WRONLY); // both have a value, when you use exclusive or, it creates a new value which defines the logical or behaviour

    if(dst<0)
    {

        printf(2, "cp: cannot open %s\n", argv[2]);
        exit();

    }

    printf(1,"src fd : %d\n",src);
    printf(1,"src fd : %d\n",src);

    char buf[512];
    int n;

    while((n = read(src,buf,sizeof(buf))) > 0) // learn how the read system call works
    {

        write(dst,buf,n); // learn how to write system call works

    } 

    close(src);
    close(dst);
    exit();

}