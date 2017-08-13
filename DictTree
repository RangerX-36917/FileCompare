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

node *root; //root node for the tree

//create a branch of documents which have the same size "str"
void create(long length ,char *name, char *path){ 
    char *str;
    sprintf(str, "%ld", length);
    int len = strlen(str);
    node *p = root;
    for (int i = 0; i < len; i++){
       int in = str[i] - '0';
       if (p->next[in] == NULL){
           p->next[in] = (node *)malloc(sizeof(node));  
       }
         p = p->next[in];
    }

    p->docu = (document *)malloc(sizeof(document));
    p->docu->fname = name;
    p->docu->fpath = path;
    p->docu->next = NULL;
}

//check if a branch of documents with size length exists 
bool query(long length){
    char *str;
    sprintf(str, "%ld", length);
    int len = strlen(str);
    node *p = root, *q;
    for (int i = 0; i < len; i++){
        int in = str[i] - '0';
        if (p->next[in] == NULL) return 0;
        else p = p->next[in];
    }
    return 1;
}

//go through the branch of size length
void output(long length){
    char *str;
    sprintf(str, "%ld", length);
    int len = strlen(str);

    node *p = root; 
    document *q;
    int in;
    for (int i = 0; i < len; i++){
      in = str[i] - '0';
      p = p->next[in];
    }
    q = p->docu;
    while (q->next != NULL) {
        char *ch;
        printf("%s\n", q->fname);
        printf("%s\n", q->fpath);
        q = q->next;
    }   
    printf("%s\n", q->fname);
    printf("%s\n", q->fpath);
    
   
}

void insertf(long length, char *name, char *path) {
    char *str;
    sprintf(str, "%ld", length);
    int len = strlen(str);
    
    node *p = root; 
    document *q;
    int in;
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
    q->next = (document *)malloc(sizeof(document));
    q = q->next;
    q->fname = name;
    q->fpath = path;
    q->next = NULL;
}
void freedocu(document *ptr) {
    if (ptr->next != NULL) {
        freedocu(ptr->next);
    }
    free(ptr);
}
void freetree(node *ptr){
    if (ptr->docu != NULL) {
        freedocu(ptr->docu);
    }
    for (int i = 0; i < 10;i++){
        if (ptr->next[i] != NULL) freetree(ptr->next[i]);
    }
    free(ptr);
}

int main(){
  file f;
    int t,n;
    char size[100];
   
    root = (node *)malloc(sizeof(node)); //allocate memory for dictionary tree
    for (int i = 0;i < 10; i++)
      root->next[i] = NULL;

   
    return 0;
}

