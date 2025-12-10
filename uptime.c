#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{

    if(argc!= 1)
    {

        printf(2,"Usage: uptime\n");
        exit();

    }

    printf(1,"Uptime : %d\n",uptime());
    exit();

}

// the gist of this lab is to find useful system calls from user.h and apply them to make cli commands