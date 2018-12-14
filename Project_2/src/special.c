#include <stdio.h>
#include <stdint.h>

#include "../inc/special.h"
#include "../inc/tools.h"

int special(int argc, char* argv[])
{
    printf("Special start\n");
    int n;
    for(n=0; n<argc; n++)
        printf("Special: #%d %s\n", n, argv[n]);

    printf("Special end\n");
    return 0;
}