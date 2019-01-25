/*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../inc/mfs.h"
#include <iostream>

using namespace std;



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
    metadata_t metadata;
    uint32_t addr;
    MFS* fs = new MFS(name);
    if( fs->lastCode!=OK )
    {
        delete fs;
        return nullptr;
    }

    return fs;
}

MFS::returnCode MFS::unmountFileSystem(MFS* fileSystem)
{
    if(fileSystem)
    {
        fseek(fileSystem->disc, 0, 0);
        fwrite(&fileSystem->fileSystemHeader, sizeof(fileSystemHeader_t), 1, fileSystem->disc);
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
        return nullptr;
    // znaleziono miejsce w przestrzeni danych
    // uzupelnienie struktury metadata
    fileSystemHeader.fileDataUsed += *size;
    fileSystemHeader.metaDataUsed++;
    metadata.size = *size;
    strcpy(metadata.fileName, fileName);
    metadata.used = true;
    // zapisanie metadanych na dysk
    fseek(disc, addr, 0);
    fwrite(&metadata, sizeof(metadata_t), 1, disc);
    // stworzenie handle pliku
    fileHandle = new fileHandle_t;
    *fileHandle = addr;
    lastCode = OK;
    
    return fileHandle;
}

uint32_t MFS::allocData(uint32_t size)
{
    metadata_t metadata;
    dataBlock_t dataBlock;
    dataBlock.base = 0;
    lastCode = NoEnoughDataSpace;

    if(fileSystemHeader.metaDataUsed==0)
    {
        lastCode = OK;  
        cout<<"|printf0|";
        return fileSystemHeader.fileDataStart;
    }

    // stworzenie mapy zajetosci sekcji danych
    fseek(disc, fileSystemHeader.metadataStart, 0);
    for(uint32_t n=0; n<fileSystemHeader.metaDataUsed; n++)
    {
        fread(&metadata, sizeof(metadata_t), 1, disc);
        if( metadata.used )
        {
            dataMap[n].base = metadata.base;
            dataMap[n].size = metadata.size;
            dataMap[n].metadataAddr = fileSystemHeader.metadataStart;
            dataMap[n].metadataAddr+= n*sizeof(metadata_t); 
        }     
    }

    // sortowanie zajetych obszarow
    for(uint32_t i=0; i<(fileSystemHeader.metaDataUsed-1); i++)
        for(uint32_t j=0; j<(fileSystemHeader.metaDataUsed-1); j++)
            if( dataMap[j].base > dataMap[j+1].base )
            {
                dataBlock_t tmp;
                tmp = dataMap[j];
                dataMap[j] = dataMap[j+1];
                dataMap[j+1] = dataMap[j];
            }

    if((dataMap[0].base-fileSystemHeader.fileDataStart)>=size)
    {
        lastCode = OK;  
        cout<<"|printf1|";
        return fileSystemHeader.fileDataStart;
    }

    for(int n=1; n<(fileSystemHeader.metaDataUsed-1); n++)
        if( dataMap[n].base - dataMap[n-1].base - dataMap[n-1].size >= size )
        {
            lastCode = OK;
            cout<<"|printf2|";
            return dataMap[n-1].base + dataMap[n-1].size;
        }
    
    if( fileSystemHeader.fileSystemSize-dataMap[fileSystemHeader.metaDataUsed-1].base-dataMap[fileSystemHeader.metaDataUsed-1].size )
    {
        lastCode = OK;
        cout<<"|printf3|";
        return dataMap[fileSystemHeader.metaDataUsed-1].base + dataMap[fileSystemHeader.metaDataUsed-1].size;
    }

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
            *fileSize = metadata.size;
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
    metadata_t metadata;

    fseek(disc, *fileHandle, 0);
    fread(&metadata, sizeof(metadata_t), 1, disc);

    if( metadata.size<(offset+length) )
        return ReadDataSizeError;
    
    fseek(disc, metadata.base+offset, 0);
    fread(dest, length, 1, disc);
    return OK;
}

MFS::returnCode MFS::writeFile( const fileHandle_t* fileHandle, const void* src, uint32_t offset, uint32_t length )
{    
    metadata_t metadata;

    fseek(disc, *fileHandle, 0);
    fread(&metadata, sizeof(metadata_t), 1, disc);

    if( metadata.size<(offset+length) )
        return WriteDataSizeError;
    
    fseek(disc, metadata.base+offset, 0);
    fwrite(src, length, 1, disc);
    return OK;
}

MFS::returnCode MFS::deleteFile( const char* fileName )
{
    fileHandle_t* fileHandle;
    uint32_t n = 1;
    metadata_t metadata;

    fileHandle = openFile(fileName, fileMode_t::READ, &n);

    if( fileHandle==nullptr )
        return NotFound;

    fseek(disc, *fileHandle, 0);
    fread(&metadata, sizeof(metadata_t), 1, disc);
    metadata.used = false;
    fileSystemHeader.fileDataUsed -= metadata.size;
    fileSystemHeader.metaDataUsed--;
    fseek(disc, *fileHandle, 0);
    fwrite(&metadata, sizeof(metadata_t), 1, disc);
    return OK;
}

MFS::returnCode MFS::fileList()
{
    metadata_t metadata;
    uint32_t addr;

    fseek(disc, fileSystemHeader.metadataStart, 0);
    for(addr = fileSystemHeader.metadataStart; 
        addr<fileSystemHeader.fileDataStart; 
        addr+=sizeof(metadata_t)
        )
    {
        fread(&metadata, sizeof(metadata_t), 1, disc);
        if( metadata.used )
        {
            cout<<"FileName: \""<<metadata.fileName<<"\"; Base: "<<metadata.base<<"; Size: "<<metadata.size<<endl;
        }       
    }


    return OK;
}

MFS::MFS(const char* fileSystemName)
{
    //uint32_t size = strlen(fileSystemName);
    
    strcpy(this->fileSystemName, fileSystemName);
    dataMap = nullptr;

    disc = fopen(fileSystemName, "r+");
    if(disc==nullptr)
    {
        lastCode = DiscFileError;
        return;
    }

    fread(&fileSystemHeader, sizeof(fileSystemHeader_t), 1, disc);

    if(0!=strcmp(fileSystemHeader.guardText, FileSystemGuardText))
    {
        lastCode = GuardTextMismatch;
        return;
    }
    
    dataMap = new dataBlock_t[fileSystemHeader.metadataIndex];

    lastCode = OK;
}

MFS::~MFS()
{
    if(disc!=nullptr)
        fclose( disc );    
    if( dataMap!=nullptr)
        delete[] dataMap;
}