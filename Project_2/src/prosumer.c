#include <stdio.h>
#include <stdint.h>

#include "../inc/prosumer.h"
#include "../inc/tools.h"

int prosumer(int argc, char* argv[])
{
    printf("Prosumer start\n");
    int n;
    for(n=0; n<argc; n++)
        printf("Prosumer: #%d %s\n", n, argv[n]);

    printf("Prosumer end\n");
    return 0;
}
