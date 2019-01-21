/*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../inc/mfs.h"


void info( const char* info)
{
    printf("%s", info);
}


int MFS::makeFileSystem( const char* name, uint32_t size )
{
    FILE* file = fopen(name, "w");

    char *ptr = new char[size];
    memset(ptr, 0, size);
    //TO DO: set filesystem structures initial data

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
}