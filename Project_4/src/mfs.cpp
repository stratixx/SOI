/*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../inc/mfs.h"



MFS::returnCode MFS::makeFileSystem( const char* name, uint32_t size )
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
    return OK;
}

MFS* MFS::mountFileSystem(const char* name)
{
    return new MFS(name);
}

MFS::returnCode MFS::unmountFileSystem(MFS* fileSystem)
{
    if(fileSystem)
    {
        delete fileSystem;
    }
    return OK;
}

MFS::fileHandle_t* MFS::createFile( const char* fileName, uint32_t* size)
{

}

MFS::fileHandle_t* MFS::openFile( const char* fileName, fileMode_t mode, uint32_t* fileSize)
{
    fileHandle_t* fileHandle;
    metadata_t metadata;
    uint32_t addr;

    fseek(disc, fileSystemHeader.metadataStart, 0);
    for(addr = fileSystemHeader.metadataStart; 
        addr<fileSystemHeader.fileDataStart; 
        addr+=sizeof(metadata_t)
        )
    {
        fread(&metadata, sizeof(metadata_t), 1, disc);
        if( metadata.used && (0==strcmp(metadata.fileName, fileName)) )
            break;        
    }

    if(addr>=fileSystemHeader.fileDataStart)
    {
        // pliku nie znaleziono
        if(mode&fileMode_t::CREATE)

        return nullptr;
    }
    else
    {
        // plik znaleziony

        fileHandle = new fileHandle_t;
        *fileHandle = addr;
    }

    return fileHandle;
}

MFS::returnCode MFS::closeFile( fileHandle_t* fileHandle )
{
    if( fileHandle!=nullptr )
        delete fileHandle;
    
    return OK;
}

MFS::returnCode MFS::readFile( const fileHandle_t* fileHandle, void* dest, uint32_t offset, uint32_t length )
{
    return UNIMPLEMENTED;
}

MFS::returnCode MFS::writeFile( const fileHandle_t* fileHandle, const void* src, uint32_t offset, uint32_t length )
{
    return UNIMPLEMENTED;
}

MFS::returnCode MFS::deleteFile( const char* fileName )
{
    return UNIMPLEMENTED;
}


MFS::MFS(const char* fileSystemName)
{
    //uint32_t size = strlen(fileSystemName);
    
    strcpy(this->fileSystemName, fileSystemName);

    disc = fopen(fileSystemName, "r+");
    fread(&fileSystemHeader, sizeof(fileSystemHeader_t), 1, disc);
}

MFS::~MFS()
{
    fclose( this->disc );    
}