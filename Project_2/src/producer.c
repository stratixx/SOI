#include <stdio.h>
#include <stdint.h>

#include "../inc/producer.h"
#include "../inc/tools.h"

int producer(int argc, char* argv[])
{
    printf("Producer start\n");
    int n;
    for(n=0; n<argc; n++)
        printf("Producer: #%d %s\n", n, argv[n]);

    printf("Producer end\n");
    return 0;
}