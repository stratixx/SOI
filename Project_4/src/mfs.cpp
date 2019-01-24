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
    fileSystemHeader.metaDataUsed   = 0;
    fileSystemHeader.fileDataStart  = fileSystemHeader.metadataStart;
    fileSystemHeader.fileDataStart += fileSystemHeader.metadataIndex*sizeof(metadata_t);
    fileSystemHeader.fileDataSize   = size - fileSystemHeader.fileDataStart;
    fileSystemHeader.fileDataUsed   = 0;

    memset(ptr, 0, size);
    memcpy(ptr, &fileSystemHeader, sizeof(fileSystemHeader_t));
    fwrite(ptr, size, 1, file);
    fclose(file);
    delete[] ptr;
    return OK;
}

MFS* MFS::mountFileSystem(const char* name)
{
    MFS* fs = new MFS(name);
    if( fs->lastCode!=OK )
    {
        delete fs;
        return nullptr;
    }
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
    fileHandle_t* fileHandle = nullptr;
    metadata_t metadata;
    uint32_t addr;

    fseek(disc, fileSystemHeader.metadataStart, 0);
    // szukanie wolnego slotu metadata
    for(addr = fileSystemHeader.metadataStart; 
        addr<fileSystemHeader.fileDataStart; 
        addr+=sizeof(metadata_t)
        )
    {
        fread(&metadata, sizeof(metadata_t), 1, disc);
        if( !metadata.used )
            break; 
    }

    if(addr>=fileSystemHeader.fileDataStart)
    {
        lastCode = MetaDataArrayFull;
        return nullptr;
    }

    // znaleziono wolny slot metadata, szukanie miejsca w przestrzeni danych
    metadata.base = allocData(*size);
    if(metadata.base==0)
    {
        lastCode = NoEnoughDataSpace;
        return nullptr;
    }
    // znaleziono miejsce w przestrzeni danych
    // uzupelnienie struktury metadata
    metadata.size = *size;
    strcpy(metadata.fileName, fileName);
    metadata.used = true;
    // zapisanie metadanych na dysk
    fseek(disc, addr, 0);
    fwrite(&metadata, sizeof(metadata), 1, disc);
    lastCode = OK;
    

    return fileHandle;
}

uint32_t MFS::allocData(uint32_t size)
{
    return 0;
}

MFS::fileHandle_t* MFS::openFile( const char* fileName, fileMode_t mode, uint32_t* fileSize)
{
    fileHandle_t* fileHandle = nullptr;
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
        {
            // stwórz plik
            fileHandle = createFile(fileName, fileSize);      
        }
        else 
        {
            // nie zadano stworzenia pliku
            lastCode = NotFound;
        }        
    }
    else
    {
        // plik znaleziono
        if(mode&fileMode_t::CREATE) 
        {
            // próba stworzenia istniejącego pliku
            lastCode = Exist;       
        }
        else 
        {
            // plik znaleziony, ustaw wskazanie na strukture metadata pliku
            fileHandle = new fileHandle_t;
            *fileHandle = addr;
            lastCode = OK;
        }      
    }

    return fileHandle;
}

MFS::returnCode MFS::closeFile( fileHandle_t* fileHandle )
{
    if( fileHandle!=nullptr )
        delete fileHandle;
    lastCode = OK;
    return OK;
}

MFS::returnCode MFS::readFile( const fileHandle_t* fileHandle, void* dest, uint32_t offset, uint32_t length )
{
    return Unimplemented;
}

MFS::returnCode MFS::writeFile( const fileHandle_t* fileHandle, const void* src, uint32_t offset, uint32_t length )
{
    return Unimplemented;
}

MFS::returnCode MFS::deleteFile( const char* fileName )
{
    return Unimplemented;
}


MFS::MFS(const char* fileSystemName)
{
    //uint32_t size = strlen(fileSystemName);
    
    strcpy(this->fileSystemName, fileSystemName);

    disc = fopen(fileSystemName, "r+");
    fread(&fileSystemHeader, sizeof(fileSystemHeader_t), 1, disc);

    if(0==strcmp(fileSystemHeader.guardText, FileSystemGuardText))
        lastCode = OK;
    else
        lastCode = GuardTextMismatch;
    
}

MFS::~MFS()
{
    fclose( this->disc );    
}