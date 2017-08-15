#include <iostream>
#include "DictTree.h" 
#include "MyFile.h"
//create a branch of documents which have the same size "str"
void DictTree::create(long length ,char *name, char *path, node *root){ 

    int in = 0;
    char str[20];
    sprintf(str, "%ld", length);
    int len = strlen(str);
    node *p = root;
    //find the position of the document list in the tree and create a path to the position
    for (int i = 0; i < len; i++){
        int in = str[i] - '0';
        if (p->next[in] == NULL){
           if((p->next[in] = (node *)malloc(sizeof(node))) == NULL){
            fprintf(stderr,"cant reserve memory!");
            abort(); 
           } 
           for (int i = 0; i < 10; i++) {
             p->next[in]->next[i] = NULL;
           }
           p->next[in]->docu = NULL;
        }
        p = p->next[in];
       
        in = 0;
    }
    //create document list
    if((p->docu = (document *)malloc(sizeof(document))) == NULL ) {
        //memset(p->docu, '\0', sizeof(document));
            fprintf(stderr,"cant reserve memory!");
            abort(); 
           } 
    p->docu->next = NULL;

    strcpy(p->docu->fpath, path);
    strcpy(p->docu->fname, name);
}

//check if a list of documents of size length exists 
bool DictTree::query(long length, node *root){
    int in = 0;
    char str[20];
    sprintf(str, "%ld", length);
    int len = strlen(str);
    node *p = root;
    for (int i = 0; i < len; i++){
        in = str[i] - '0';
        if (p->next[in] == NULL) return 0;
        else p = p->next[in];
    }
    if (p->next[10] != NULL) return 1;
    else return 0;
}

//go through the list of size length and compare files
int DictTree::ListDocu(long length, const char *path, const char *name, node *root){

    node *p = root; 
    document *q;
    //find position of document list in the Dictionary tree
    char str[20];
    sprintf(str, "%ld", length);
    int len = strlen(str);
    int in;
    for (int i = 0; i < len; i++){
      in = str[i] - '0';
      
        p = p->next[in];
    }
    //generate full path
    q = p->docu;
    std::string path1 = path;
    path1 += '/';
    path1 += name;
    
    std::string path2 = q->fpath;
    path2 += '/';
    path2 += q->fname;
   
    if (docuCheck(q, path1)) return 1;\
    else return 0;
    
    return 1;
  
    
}

void DictTree::insertf(long length, char *_name, char *_path, node *root) {
    // printf("call create");
    int in = 0;
    char str[20];
    sprintf(str, "%ld", length);
    int len = strlen(str);
    node *p = root;

    p = root; 
    document *q;
    //get to the node of size str
    for (int i = 0; i < len ; i++){
      in = str[i] - '0';
      p = p->next[in];
    }
    //get to the end of docu list of size ptr
    q = p->docu;
    while (q->next !=NULL) {
        q = q->next;
    }    
    //insert document
    if((q->next = (document *)malloc(sizeof(document))) == NULL) {
        memset(q->next, '\0', sizeof(document));
            fprintf(stderr,"cant reserve memory!");
            abort(); 
           } 
    q = q->next;
    q-> next= NULL;
    strcpy(q->fpath, _path);
    strcpy(q->fname, _name);
    
}
void DictTree::freedocu(document *ptr) {
    if (ptr->next != NULL) {
        freedocu(ptr->next);
    } 
     free(ptr);
}
void DictTree::freetree(node *ptr){
    if (ptr->docu != NULL) {
        freedocu(ptr->docu);
    }
  
    for (int i = 0; i < 10;i++){
        if (ptr->next[i] != NULL) {
            freetree(ptr->next[i]);
        } 
    }
   free(ptr);
   
}
int DictTree::docuCheck(document *q, std::string path1) {
    std::string path2 = q->fpath;
    path2 += '/';
    path2 += q->fname;

    if (MyFile::Compare(path1, path2)) {
        std::cout << path2 << '\t' << "is identical to" << '\t' << path1 << std::endl;\
        return 1;\
    } //else \
        if (q->next != NULL) \
            docuCheck(q->next, path1);
    return 0;
}
