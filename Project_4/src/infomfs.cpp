/*
*
*
*/

#include "../inc/infomfs.h"
#include "../inc/mfs.h"

int main(int argc, char * argv[])
{
	int n=0;
	for(n=0; n<argc; n++)
	{
		info(argv[n]);
		info("\n\r");
	}
	info("\n\r");

	return 0;
}
