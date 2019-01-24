/*
*
*
*/


#ifndef mfs_H
#define mfs_H


#include <stdio.h>
#include <stdint.h>

#define FILENAME_MAX_LENGTH 255
#define FILESYSTEMNAME_MAX_LENGTH 255
#define FileSystemGuardText "MFS v0.2.0     "
#define FileSystemGuardLength (sizeof(FileSystemGuardText))


class MFS
{
    public:

    typedef struct
    {
        // Nagłówek systemu plików MFS
        char guardText[FileSystemGuardLength];
        // Rozmiar dysku
        uint32_t fileSystemSize;
        // adres początku sekcji metadanych
        uint32_t metadataStart;
        // max ilość obiektów metadanych
        uint32_t metadataIndex;
        // ilość uzytych obiektów metadata - ilość plików
        uint32_t metaDataUsed;
        // adres początku sekcji danych plików
        uint32_t fileDataStart;
        // rozmiar sekcji danych plików
        uint32_t fileDataSize;
        // ilosc zajetego miejsca
        uint32_t fileDataUsed;

    }fileSystemHeader_t;

    typedef struct
    {
        bool used;
        uint32_t base;
        uint32_t size;
        char fileName[FILENAME_MAX_LENGTH];
    }metadata_t;

    typedef uint32_t fileHandle_t;

    typedef enum
    {
        READ = 1<<0,
        CREATE = 1<<1, 
        WRITE = 1<<2
    }fileMode_t;

    typedef enum
    {
        OK = 0,
        Unimplemented = -1,
        NotFound = -2, 
        Exist = -3, 
        CreateError = -4, 
        GuardTextMismatch = -5, 
        MetaDataArrayFull = -6,
        NoEnoughDataSpace = -7
    }returnCode;

    #define METADATA_T_SIZE (sizeof(metadata_t))

    char fileSystemName[255];
    fileSystemHeader_t fileSystemHeader;
    FILE* disc;
    returnCode lastCode;

    static returnCode makeFileSystem( const char* name, uint32_t size );
    static MFS* mountFileSystem(const char* name);
    static returnCode unmountFileSystem(MFS* fileSystem); 

    fileHandle_t* openFile( const char* fileName, fileMode_t mode, uint32_t* fileSize);
    returnCode closeFile( fileHandle_t* fileHandle );
    returnCode readFile( const fileHandle_t* fileHandle, void* dest, uint32_t offset, uint32_t length );
    returnCode writeFile( const fileHandle_t* fileHandle, const void* src, uint32_t offset, uint32_t length );
    returnCode deleteFile( const char* fileName );

    private:
    MFS(const char* fileSystemName);
    ~MFS();
    fileHandle_t* createFile( const char* fileName, uint32_t* size);
    uint32_t allocData(uint32_t size);
};


#endif
