#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <iostream> 
#include "MyFile.h"
#include "DictTree.h"
//11612028_11612030_11612007
int count;
using namespace std;
void printdir(const char *dir, const string fdir = "", node *root = NULL) {
  
  DIR *dp;
  struct dirent *entry;
  struct stat statbuf;
  string path;
  if((dp = opendir(dir)) == NULL) {
    fprintf(stderr, "cannot open directory: %s\n", dir);
    return;
  }
  chdir(dir);
  while ((entry = readdir(dp)) != NULL) {
    lstat(entry->d_name, &statbuf);
    if (S_ISDIR(statbuf.st_mode)) {
      if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) 
	continue;


      
      path = fdir +  dir;
      printdir(entry->d_name,path +'/' ,root);
      
    }
    else  {
      
        path = fdir + dir ;
      
     
      {
        long _len;
        char *_name, *_path;
        _name = entry->d_name;
        _path = (char*)path.c_str();
        _len = statbuf.st_size;

        cout << endl << "#" << ++count;
        //cout << " Processing " << _path << ":";\
        printf("%s (%ld bytes)...\t  ->%p", _name, _len, root);
        //start processing
        if(DictTree::query(_len, root)) {\
          if (!DictTree::ListDocu(_len, _path, _name, root)){}
         DictTree::insertf(_len, _name, _path, root);
        } else 
        {\
          DictTree::create(_len,_name,_path, root);\
        }
      }
    }

  }
 
  chdir("..");
  closedir(dp);
}

int main(int argc, char** argv) {
  //return 0;
  node *root = (node*)malloc(sizeof(node));
    for(int i = 0; i < 10; i++)
        root->next[i] = NULL;
    root->docu = NULL;
    string direc = "/home";
    if (argc !=2) {
        char* d = argv[0];
        printf("Please enter a scan path as command line argument!\nexample: %s /home/\n", d);
        exit(1);
        
    } else {
        char* d = argv[1];
        if (d[0] != '/') {
            printf("Invalid path!");
            exit(1);
        } else {
            direc = d;
            if (d[direc.length() - 1] == '/') {
                d[direc.length() - 1] = '\0';
                direc = d;
            }
        }
    }    
    printdir(direc.c_str(), "", root);
    //printf("\nAll done.\n");
    DictTree::freetree(root);
    //printf("finish free\n");
    
    
    exit(0);
}
