/*
*
*
*/


#ifndef mfs_H
#define mfs_H


#include <stdint.h>

#define FILENAME_MAX_LENGTH 255


class MFS
{
    public:

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
        OPEN = 1<<0,
        CREATE = 1<<1, 
        WRITE = 1<<2
    }openFileMode_t;

    #define METADATA_T_SIZE (sizeof(metadata_t))

    char fileSystemName[255];

    static int makeFileSystem( const char* name, uint32_t size );
    static MFS* mountFileSystem(const char* name);
    static int unmountFileSystem(MFS* fileSystem); 

    fileHandle_t openFile( const char* fileName, openFileMode_t mode, uint32_t* fileSize);
    int closeFile( const fileHandle_t fileHandle );
    int readFile( const fileHandle_t fileHandle, void* dest, uint32_t offset, uint32_t length );
    int writeFile( const fileHandle_t fileHandle, const void* src, uint32_t offset, uint32_t length );
    int deleteFile( const fileHandle_t fileHandle );

    private:
    MFS(const char* fileSystemName);
};




void info( const char* info);


#endif
