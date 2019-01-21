/*
*
*
*/

#include "../inc/mkmfs.h"
#include "../inc/mfs.h"
#include <stdlib.h>

int main(int argc, char * argv[])
{
	if(argc>2)
	{
		MFS::makeFileSystem(argv[1], atoi(argv[2]));
	}

	return 0;
}