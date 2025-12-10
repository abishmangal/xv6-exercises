#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[])
{

    if(argc != 3)
    {

        printf(2,"Usage: mv oldname newname\n");
        exit();

    }

    if(link(argv[1],argv[2]) < 0)
    {

        printf(2,"mv: cannot link %s to %s\n", argv[1], argv[2]);
        exit();

    }

    exit();

}
