#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[])
{

    if(argc != 2)
    {

        printf(2, "Usage touch filename\n");
        exit();

    }

    int fd = open(argv[1],O_CREATE|O_WRONLY);

    if(fd<0)
    {

        printf(2,"touch: cannot create %s\n", argv[1]);
        exit();

    }


    close (fd);
    exit();

}