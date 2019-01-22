/*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../inc/mfs.h"



int MFS::makeFileSystem( const char* name, uint32_t size )
{
    FILE* file = fopen(name, "w");
    char *ptr = new char[size];
    fileSystemHeader_t fileSystemHeader;

    strcpy(fileSystemHeader.guardText, FileSystemGuardText);
    fileSystemHeader.fileSystemSize = size;
    fileSystemHeader.metadataStart  = sizeof(fileSystemHeader_t);
    fileSystemHeader.metadataIndex  = size/(4*1024);
    fileSystemHeader.fileDataStart  = fileSystemHeader.metadataStart;
    fileSystemHeader.fileDataStart += fileSystemHeader.metadataIndex*sizeof(metadata_t);
    fileSystemHeader.fileDataSize   = size - fileSystemHeader.fileDataStart;

    memset(ptr, 0, size);
    memcpy(ptr, &fileSystemHeader, sizeof(fileSystemHeader_t));
    fwrite(ptr, size, 1, file);
    fclose(file);
    delete[] ptr;
    return 0;
}

MFS* MFS::mountFileSystem(const char* name)
{
    return new MFS(name);
}

int MFS::unmountFileSystem(MFS* fileSystem)
{
    if(fileSystem)
        delete fileSystem;
    return 0;
}


MFS::fileHandle_t MFS::openFile( const char* fileName, fileMode_t mode, uint32_t* fileSize)
{
    fileHandle_t handle;
    return handle;
}

int MFS::closeFile( const fileHandle_t fileHandle )
{
    return -1;
}

int MFS::readFile( const fileHandle_t fileHandle, void* dest, uint32_t offset, uint32_t length )
{
    return -1;
}

int MFS::writeFile( const fileHandle_t fileHandle, const void* src, uint32_t offset, uint32_t length )
{
    return -1;
}

int MFS::deleteFile( const char* fileName )
{
    return -1;
}


MFS::MFS(const char* fileSystemName)
{
    //uint32_t size = strlen(fileSystemName);
    
    strcpy(this->fileSystemName, fileSystemName);

    FILE* file = fopen(fileSystemName, "r");
    fread(&fileSystemHeader, sizeof(fileSystemHeader_t), 1, file);
    fclose(file);
}