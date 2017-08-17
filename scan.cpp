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

using namespace std;

int count = 0, detail = 0;
string direct;
FILE *fpOut;
void processArgs(int argc, char** argv);
void printdir(const char *dir, const string fdir, node *root);


int main(int argc, char** argv) {
  processArgs(argc, argv);
  //get the path where the program is stored
  char workPath[200];
  getcwd(workPath, 200);
  //open cache file
  fpOut = fopen("result.data", "w");
  //initialize dictionary tree
  node *root = (node*)malloc(sizeof(node));
  for(int i = 0; i < 10; i++)
    root->next[i] = NULL;
  root->docu = NULL;
    
 
  //work and close file pointer  
  printdir(direct.c_str(), "", root);
  fclose(fpOut);

  //free dictionary tree
  DictTree::freetree(root);
  //enter original directory and read cache file
  chdir(workPath); 
  DIR *dir;
  dir = opendir(workPath);
  printf("\nThe duplicated files are:\n");
  system("cat result.data");
  //delete cache file
  system("rm -rf result.data");
  closedir(dir);
  exit(0);
}
//process command line argumentation
void processArgs(int argc, char** argv) {
  int opt = 0;
  opterr = 0;
    while ((opt = getopt(argc, argv, "dh")) != -1) {
      switch (opt) {
      case 'd':
        detail = 1;
        break;
      case 'h':
        system("cat README");
        exit(1);
        break;
      case '?':
        printf("Scan: '%c' is not a valid option. See './scan -h'\n", optopt);
        exit(1);
        break;
      }
    }

    if (argc == 1)  direct = "/home";
    else {
      char* d = argv[optind];
    if (d[0] != '/') {
        printf("Invalid path!");
        exit(1);
    } else {
        direct = d;
        if (d[direct.length() - 1] == '/') {
            d[direct.length() - 1] = '\0';
            direct = d;
        }
      }
    }

}
//go through designated directory and find duplicated files
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
    //if processing a directory
    if (S_ISDIR(statbuf.st_mode)) {
      //skip '.' and '..'
      if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) 
        continue;
      //generate pull path and proceed
      path = fdir +  dir;
      printdir(entry->d_name,path +'/' ,root);
    }
    else  { //of processing file
      path = fdir + dir ;
      long _len;
      char *_name, *_path;
      _name = entry->d_name;
      _path = (char*)path.c_str();
      _len = statbuf.st_size;
      if (detail) {
        cout << " Processing " << "#" << ++count << ":" << _path << ":";\
        printf("%s (%ld bytes)...\n", _name, _len); 
      }
      //start processing
      if(DictTree::query(_len, root)) {
        if (!DictTree::ListDocu(_len, _path, _name, root, fpOut)){}
        DictTree::insertf(_len, _name, _path, root);
      } else DictTree::create(_len,_name,_path, root);
    }
  }
//return the the previous directory
chdir("..");
closedir(dp);
}