/*
*
*
*/

#include "../inc/cpmfs.h"
#include "../inc/mfs.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	MFS * fs;
	MFS::fileHandle_t* fileMFS;
	uint32_t fileMFSsize;
	MFS::returnCode result;
	FILE* fileH;

	for(int n=0; n<argc; n++)
		cout<<argv[n]<<endl;
	

	cout<<"----------------"<<endl;

	if(argc<=4 || ((0!=strcmp("-TO", argv[1])) && (0!=strcmp("-FROM", argv[1]))) )
	{
		usage_of_cpmfs();
		return -1;
	}

	fs = MFS::mountFileSystem(argv[2]);

	if( 0==strcmp("-TO", argv[1]) )
	{
		cout<<"Linux --> MFS"<<endl;

		for(int n=3; n<argc; n++)
		{
			cout<<argv[n]<<"... ";
			fileMFS = fs->openFile(argv[n], MFS::fileMode_t::CREATE, &fileMFSsize);
			if(fileMFS==nullptr)
			{
				cout<<"MFS openFile error"<<endl;
				continue;
			}

			cout<<"ok"<<endl;
			fs->closeFile(fileMFS);
		}
	}
	else
	{
		cout<<"MFS --> Linux"<<endl;

		for(int n=3; n<argc; n++)
		{
			cout<<argv[n]<<"... ";

			cout<<"unimpl"<<endl;
		}
	}
		
	MFS::unmountFileSystem(fs);
	return 0;
}

void usage_of_cpmfs()
{
	cout<<"Usage: cpmfs -TO <fileSystemName> <linuxFile0> <linuxFile1> ..."<<endl;
	cout<<"Usage: cpmfs -FROM <fileSystemName> <MFSFile0> <MFSFile1> ..."<<endl;

}