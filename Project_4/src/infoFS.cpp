/*
*
*
*/

#include "../inc/infoFS.h"
#include "../inc/malditoFS.h"

int main(int argc, char * argv[])
{
	int n=0;
	for(n=0; n<argc; n++)
	{
		info(argv[n]);
		info(" ");
	}
	info("\n\r");

	return 0;
}
