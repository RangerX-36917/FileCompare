#ifndef __DICTTREE__
#define __DICTTREE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct document{
    char *fname,*fpath; //store name and path of a document
    document *next = NULL; //pointer to the next document of the same size
}file;

struct node{
    node *next[10]; //pointers to digits
    document *docu; //pointers to documents
};

class DictTree{
    
    public:
    static node *root; //root node for the tree
    void create(long length ,char *name, char *path);
    bool query(long length);
    void output(long length);
    void insertf(long length, char *name, char *path);
    void freedocu(document *ptr);
    void freetree(node *ptr);
};
#endif

