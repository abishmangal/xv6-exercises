#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{

    if(argc!= 0)
    {

        printf(2,"usage: uptime");
        exit();

    }

    printf("Uptime : %d",uptime());
    exit();

}