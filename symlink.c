#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf(2, "Usage: ln target linkpath\n");
        exit();
    }

    if(symlink(argv[1], argv[2]) < 0)
    {
        printf(2, "symlink failed\n");
        exit();
    }

    exit();
}
