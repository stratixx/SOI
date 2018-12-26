#ifndef MAIN_H
#define MAIN_H


void fork_child(int (*child)(int, char**), int argc, char * argv[]);


#endif
