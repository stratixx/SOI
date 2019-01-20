/*
*
*
*/

#include <stdio.h>
#include "../inc/mfs.h"


void info( const char* info)
{
    printf("%s", info);
}


int MFS::makeFileSystem( const char* name, uint32_t size )
{
    return -1;
}

MFS* MFS::mountFileSystem(const char* name)
{
    return (MFS*)nullptr;
}

int MFS::unmountFileSystem(MFS* fileSystem)
{
    return -1;
}


MFS::fileHandle_t MFS::openFile( const char* fileName, openFileMode_t mode, uint32_t* fileSize)
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

int MFS::deleteFile( const fileHandle_t fileHandle )
{
    return -1;
}


MFS::MFS(const char* fileSystemName)
{

}