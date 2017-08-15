
#include "MyFile.h"
#define multiple 64
int MyFile::Compare(std::string path1, std::string path2){
  //printf("sleep");\
  usleep(250);

  
  
  int leng1 = path1.length();
  int leng2 = path2.length();
  char *_path1 = new char[leng1 + 1];
  char *_path2 = new char[leng2 + 1];
  strcpy(_path1, path1.c_str());
  strcpy(_path2,  path2.c_str());
  int iRead;
  char *char1, *char2;
  long len1, len2;
  char1 = new char[10000];
  char2 = new char[10000];
  
  printf("\n\n **************** \n %s--vs--%s \n\n", _path1, _path2);
  
  FILE * fpIn1,  * fpIn2 ;
  if (fpIn2 = fopen (_path2, "rb"))
    printf("1->%p\t", fpIn1);
  else return 2;
  if (fpIn1 = fopen (_path1, "rb"))
    printf("2->%p\n", fpIn1);
  else return 2;
  
  //printf("pointers :->1 %p ->2 %p",fpIn1, fpIn2);
  
  if (fpIn1 && fpIn2 ) {
    while (((iRead = fread (char1, 1, sizeof (char1)*multiple, fpIn1)) > 0) && ((iRead = fread (char2, 1, sizeof (char2)*multiple, fpIn2)) > 0)){ 
       if (strcmp(char1, char2)) {
         fclose(fpIn1);
         fclose(fpIn2);
          return 0;
       } 
      }
    }else {
    fprintf (stdout, "Fail to open file！%s\n", path1.c_str()) ;
      return 2 ;
     }
     
     fclose (fpIn1);
     fclose (fpIn2);
     
     return 1;
    }

    
 
  
 
    



