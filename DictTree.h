#ifndef __DICTTREE__
#define __DICTTREE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
//node of documents
typedef struct document{
    char fname[200];//store file name
    char fpath[200];//store file path
    document *next = NULL; 
}file;

//node of dictionary tree
=======
typedef struct document{
    char *fname,*fpath; //store name and path of a document
    document *next = NULL; //pointer to the next document of the same size
}file;

>>>>>>> ffaa796f968e3a3034e54ec537834d95f1378174
struct node{
    node *next[10]; //pointers to digits
    document *docu; //pointers to documents
};

<<<<<<< HEAD


class DictTree{
    
    public:
        static void create(long length ,char *name, char *path, node *root);
        static bool query(long length, node *root);
        static int ListDocu(long length, const char *path, const char *name, node *root);
        static void insertf(long length, char *name, char *path, node *root);
        static void freedocu(document *ptr);
        static void freetree(node *ptr);
        static int docuCheck(document *ptr, std::string path1);
  
};
#endif
=======
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

>>>>>>> ffaa796f968e3a3034e54ec537834d95f1378174
