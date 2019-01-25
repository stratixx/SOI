/*
*
*
*/

#include "../inc/infomfs.h"
#include "../inc/mfs.h"
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc, char * argv[])
{
	MFS * fs;
	float eff;

	if(argc>1)
	{	
		fs = MFS::mountFileSystem(argv[1]);
		if(fs==nullptr)
		{
			cout<<"MountFileSystem error! Abort!"<<endl;
			return -2;
		}

		cout<<"name:                  \""<<fs->fileSystemName<<"\""<<endl;
		cout<<"guardText:             \""<<fs->fileSystemHeader.guardText<<"\""<<endl;
		cout<<"fileSystemSize:        "<<fs->fileSystemHeader.fileSystemSize/1024<<" KB"<<endl;
		cout<<"metadata starts at:    "<<fs->fileSystemHeader.metadataStart<<endl;
		cout<<"metadata elements:     "<<fs->fileSystemHeader.metadataIndex<<endl;
		cout<<"metadata used elements:"<<fs->fileSystemHeader.metaDataUsed<<endl;
		cout<<"fileData starts at:    "<<fs->fileSystemHeader.fileDataStart<<endl;
		cout<<"fileDataSize:          "<<fs->fileSystemHeader.fileDataSize/1024<<" KB"<<endl;
		cout<<"fileDataUsed:          "<<(float)(100.0*fs->fileSystemHeader.fileDataUsed/fs->fileSystemHeader.fileDataSize)<<"%"<<endl;
		cout<<"fileSystem efficiency: "<<(float)(100.0*fs->fileSystemHeader.fileDataSize/fs->fileSystemHeader.fileSystemSize)<<"%"<<endl;



		MFS::unmountFileSystem(fs);
	}
	else
	{
		cout<<"Usage: infomfs <fileSystemName>"<<endl;
		return -1;
	}

	return 0;
}
