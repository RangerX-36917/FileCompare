//directory traversal is adapted from "Begining Linux Programming 4th edition" by Neil Matthew and Richard Stones  
//#include "Trie.h"
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
#define LENTH 100
int count;
using namespace std;

    static void printdir(const char *dir, const string fdir = "", node *root = NULL) {
        
        bool did = false;
        string _dir;
        DIR *dp;
        struct dirent *entry;
        struct stat statbuf;
        if((dp = opendir(dir)) == NULL) {
          fprintf(stderr, "cannot open directory: %s\n", dir);
          return;
        }
        chdir(dir);
        while ((entry = readdir(dp)) != NULL) {
            lstat(entry->d_name, &statbuf);
            //if DIR
            if (S_ISDIR(statbuf.st_mode)) {
                if((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0))
                    continue;
                
                if (fdir != "")
                    printdir(entry->d_name, fdir + "/" + dir, root );
                else printdir(entry->d_name, fdir + dir, root);
                
            }
            //if FILE
            else  {
               
                if (fdir == "")
                    _dir = fdir +  dir; 
                else 
                    _dir = fdir + "/" + dir;

                char *path = (char*)_dir.c_str();
                string _name = entry->d_name;
                sprintf(path, "%s", _dir.c_str());

                char *name = (char*)_name.c_str();
                _dir += "";
                printf("#%10d", ++count);
                printf("processing:%s/%s(%ld bytes)...", (_dir+"").c_str(),entry->d_name,statbuf.st_size);
                
                did = true;

              
                if (!DictTree::query(statbuf.st_size, root)) {
                    DictTree::create(statbuf.st_size, name, path, root);
                } else { 
                    if (!DictTree::ListDocu(statbuf.st_size, path, name, root))
                    DictTree::insertf(statbuf.st_size, name, path, root);
                }
            
          
            }
            if(did) {
                printf("done.\n");
                did = !did;
            }
        }
        chdir("..");
        closedir(dp); 
        
        return;       
}   
node *root = (node *)malloc(sizeof(node));

int main(int argc, char** argv) {
    memset(root,'\0',sizeof(node));
    string direc = "/home/chris/";// = "/home/chris/Desktop";///Untitled Folder";
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
    
        
    //char dir[LENTH];
    
   
    printf("run:\n");
  
    

    printdir(direc.c_str(), "", root);
    printf("All done.\n");
    DictTree::freetree(root);
    printf("finish free");

    
    exit(0);
}

