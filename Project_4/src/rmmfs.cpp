/*
*
*
*/

#include "../inc/rmmfs.h"
#include "../inc/mfs.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char * argv[])
{
	MFS* fs;
	MFS::returnCode code;
	
	cout<<"rmmfs"<<endl;
	
	if( argc<2 || (0==strcmp("--help", argv[1])) )
	{
		cout<<"Usage: rmmfs <fileSystemName> <MFSFile0> <MFSFile1>"<<endl;
		return -1;
	}

	fs = MFS::mountFileSystem(argv[1]);
	if(fs==nullptr)
	{
		cout<<"MountFileSystem error! Abort!"<<endl;
		return -2;
	}

	for( int n=2; n<argc; n++)
	{
		cout<<"Delete file \""<<argv[n]<<"\"...";
		code = fs->deleteFile(argv[n]);
		if(code==MFS::returnCode::OK)
			cout<<"OK"<<endl;
		else
			cout<<"error: "<<code<<endl;
	}


	MFS::unmountFileSystem(fs);
	return 0;
}