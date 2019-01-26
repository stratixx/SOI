/*
*
*
*/

#include "../inc/lsmfs.h"
#include "../inc/mfs.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS* fs;

	cout<<"lsmfs"<<endl;

	if( argc<2 || (0==strcmp("--help", argv[1])) )
	{
		cout<<"Usage: lsmfs <fileSystemName>"<<endl;
		return -1;
	}

	fs = MFS::mountFileSystem(argv[1]);
	if(fs==nullptr)
	{
		cout<<"MountFileSystem error! Abort!"<<endl;
		return -2;
	}
	fs->fileList();

	MFS::unmountFileSystem(fs);

	return 0;
}