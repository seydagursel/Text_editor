#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H
#include<string.h>

#define INFO printf("\nline: %d : %s : %s\n",__LINE__,__FILE__,__func__)

struct node {
    char statement[40]; // max. 40 characters
    int next; // points to the textbuffer[] index of the next statement 
};
    
struct node textbuffer[25]; // max. 25 lines
 
int free_head=-1; // head node that points to the first free line in textbuffer[]
int inuse_head=-1; // head node that points to the first used line in textbuffer[]
int cursor_position, x;
int count = 0;

void edit(char*);
void insert(char*);
void delete();
void save(char*);

#endif
