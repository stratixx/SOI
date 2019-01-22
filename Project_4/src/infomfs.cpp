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

		cout<<"name:                  \""<<fs->fileSystemName<<"\""<<endl;
		cout<<"guardText:             \""<<fs->fileSystemHeader.guardText<<"\""<<endl;
		cout<<"fileSystemSize:        "<<fs->fileSystemHeader.fileSystemSize<<" KB"<<endl;
		cout<<"metadata starts at:    "<<fs->fileSystemHeader.metadataStart<<endl;
		cout<<"metadata elements:     "<<fs->fileSystemHeader.metadataIndex<<endl;
		cout<<"metadata used elements:"<<"---"<<endl;
		cout<<"fileData starts at:    "<<fs->fileSystemHeader.fileDataStart<<endl;
		cout<<"fileDataSize:          "<<fs->fileSystemHeader.fileDataSize<<" KB"<<endl;
		cout<<"FileSystem efficiency: "<<100.0*fs->fileSystemHeader.fileDataSize/fs->fileSystemHeader.fileSystemSize<<"%"<<endl;

		MFS::unmountFileSystem(fs);
	}
	else
	{
		cout<<"Usage: infomfs <fileSystemName>"<<endl;
	}

	return 0;
}
