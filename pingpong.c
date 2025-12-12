#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char*argv[])
{

    if(argc != 1)
    {

        printf(2,"usage: pingpong\n");
        exit();

    }

    int pipe1[2];
    int pipe2[2];

    if(pipe(pipe1)<0 || pipe(pipe2)<0)
    {

        printf(2,"pingpong: pipe failed\n");
        exit();

    }

    int pid = fork();

    if(pid < 0)
    {

        printf(2,"pingping: fork failed\n");
        exit();

    }

    if(pid == 0)
    {

        close(pipe1[0]);
        write(pipe1[1],"ping\0",5);

        char read_buffer[5];

        close(pipe2[1]);
        read(pipe2[0],read_buffer,4);

        printf(1,"%d : %s\n",getpid(),read_buffer);
        printf(1,"Recieved pong\n");


    }

    else
    {

        char read_buffer[5];

        close(pipe1[1]);
        read(pipe1[0],read_buffer,4);

        printf(1,"%d : %s\n",getpid(),read_buffer);
        printf(1,"Recieved ping\n");

        close(pipe2[0]);
        write(pipe2[1],"pong\0",5);
        wait();   // parent should wait for the child to complete to prevent zombie process

    }

    exit();

}