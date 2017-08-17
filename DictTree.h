#ifndef __DICTTREE__
#define __DICTTREE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

typedef struct document{
    char fname[200];//store file name
    char fpath[200];//store file path
    document *next = NULL; 
}file;

//node of dictionary tree
struct node{
    node *next[10]; //pointers to digits
    document *docu; //pointers to documents
};


 
class DictTree{
   
    public:
        static void create(long length ,char *name, char *path, node *root);
        static bool query(long length, node *root);
        static int ListDocu(long length, const char *path, const char *name, node *root, FILE *fpOut);
        static void insertf(long length, char *name, char *path, node *root);
        static void freedocu(document *ptr);
        static void freetree(node *ptr);
        static int docuCheck(document *ptr, std::string path1, FILE *fp);
  
};
#endif
