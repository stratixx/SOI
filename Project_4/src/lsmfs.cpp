/*
*
*
*/

#include "../inc/lsmfs.h"
#include "../inc/mfs.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS* fs;

	if( argc<2 )
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