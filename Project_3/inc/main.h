#ifndef MAIN_H
#define MAIN_H


void fork_child(void* (*child)(void*), int argc, char * argv[]);


#endif
