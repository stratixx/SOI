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
	uint32_t fileSize;
	MFS::returnCode result;
	FILE* fileH;
	char* buf;

	if(argc<4 || (0==strcmp("--help", argv[1])) || ((0!=strcmp("-TO", argv[1])) && (0!=strcmp("-FROM", argv[1]))) )
	{
		cout<<"Usage: cpmfs -TO <fileSystemName> <linuxFile0> <linuxFile1> ..."<<endl;
		cout<<"Usage: cpmfs -FROM <fileSystemName> <MFSFile0> <MFSFile1> ..."<<endl;
		return -1;
	}

	fs = MFS::mountFileSystem(argv[2]);
	if(fs==nullptr)
	{
		cout<<"MountFileSystem error! Abort!"<<endl;
		return -2;
	}

	if( 0==strcmp("-TO", argv[1]) )
	{
		cout<<"Linux --> MFS"<<endl;

		for(int n=3; n<argc; n++)
		{
			cout<<argv[n]<<"... ";

			fileH = fopen(argv[n], "r");
			fseek(fileH, 0, SEEK_END);
			fileSize = ftell(fileH);

			fileMFS = fs->openFile(argv[n], MFS::fileMode_t::CREATE, &fileSize);
			if(fileMFS==nullptr)
			{
				cout<<"MFS openFile error: "<<fs->lastCode<<endl;
				fclose(fileH);
				continue;
			}
			buf = new char[fileSize];
			fseek(fileH, 0, SEEK_SET);
			fread(buf, fileSize, 1,fileH);
			if( fs->writeFile(fileMFS, buf, 0, fileSize)!=MFS::returnCode::OK )
				cout<<"MFS writeFile error: "<<fs->lastCode<<endl;
			else
				cout<<"ok"<<endl;
			
			delete[] buf;
			fs->closeFile(fileMFS);
			fclose(fileH);
		}
	}
	else
	{
		cout<<"MFS --> Linux"<<endl;

		for(int n=3; n<argc; n++)
		{
			cout<<argv[n]<<"... ";

			fileMFS = fs->openFile(argv[n], MFS::fileMode_t::READ, &fileSize);
			if(fileMFS==nullptr)
			{
				cout<<"MFS openFile error: "<<fs->lastCode<<endl;
				continue;
			}
			buf = new char[fileSize];

			if( fs->readFile(fileMFS, buf, 0, fileSize)!=MFS::returnCode::OK )
				cout<<"MFS readFile error: "<<fs->lastCode<<endl;
			else
			{
				fileH = fopen(argv[n], "w");
				fseek(fileH, 0, SEEK_SET);
				fwrite(buf, fileSize, 1,fileH);
				fclose(fileH);
				cout<<"ok"<<endl;
			}
			
			delete[] buf;
			fs->closeFile(fileMFS);
		}
	}
		
	MFS::unmountFileSystem(fs);
	return 0;
}

void usage_of_cpmfs()
{

}