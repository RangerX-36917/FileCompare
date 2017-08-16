//directory traversal is adapted from "Begining Linux Programming 4th edition" by Neil Matthew and Richard Stones  
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <iostream> 
using namespace std;
void printdir(const char *dir, const string fdir = "") {
  
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
    if (S_ISDIR(statbuf.st_mode)) {
      if(strcmp(".", entry->d_name) == 0 ||
	 strcmp("..", entry->d_name) == 0) 
	continue;
      
      printf("%s\n", entry->d_name);
      printdir(entry->d_name, fdir + "/" + dir );
      
    }
    else  {
      string _dir = fdir + "/" + dir;
      cout << _dir << ": ";
      printf("%s\n", entry->d_name);
    }
  }
  chdir("..");
  closedir(dp);
}
int main() {
  printf("Directory scan of/home:\n");
  printf("run:");
  string direc;
  cin >> direc;
  printdir(direc.c_str());
  printf("done.\n");
  exit(0);
}
