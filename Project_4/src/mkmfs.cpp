/*
*
*
*/

#include "../inc/mkmfs.h"
#include "../inc/mfs.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS * fs;

	if(argc<3 || (0==strcmp("--help", argv[1])) )
	{
		cout<<"Usage: mkmfs <fileSystemName> <fileSystemSize[kB]>"<<endl;
		return -1;
	}
	
	MFS::makeFileSystem(argv[1], atoi(argv[2])*1024);
	

	return 0;
}