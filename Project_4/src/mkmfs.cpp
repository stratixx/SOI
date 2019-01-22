/*
*
*
*/

#include "../inc/mkmfs.h"
#include "../inc/mfs.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS * fs;

	if(argc>2)
	{
		MFS::makeFileSystem(argv[1], atoi(argv[2])*1024);
	}
	else
	{
		cout<<"Usage: mkmfs <fileSystemName> <fileSystemSize[kB]>"<<endl;
	}

	return 0;
}