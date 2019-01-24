/*
*
*
*/

#include "../inc/rmmfs.h"
#include "../inc/mfs.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS* fs;
return -1;
	fs = MFS::mountFileSystem(argv[2]);
	if(fs==nullptr)
	{
		cout<<"MountFileSystem error! Abort!"<<endl;
		return -2;
	}

	return 0;
}