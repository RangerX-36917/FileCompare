#include "MyFile.h"
#define multiple 512

bool MyFile::Compare(char *size1, char *size2){
  FILE * fpIn1,  * fpIn2 ;
  int iRead;
  char *char1, *char2;
  long len1, len2;
  char1 = new char[10000];
  char2 = new char[10000];
  
  fpIn1 = fopen (size1, "rb") ;
  fpIn2 = fopen (size2, "rb") ;
  if (!fpIn1 || !fpIn2)
    {
      fprintf (stderr, "Fail to open file！\n") ;
       
      fclose (fpIn1) ;
      fclose (fpIn2) ;

      return -1 ;
    }
  //compute the length of the files
  fseek(fpIn1, 0, SEEK_END);
  len1 =ftell(fpIn1);
  fseek(fpIn1, 0, SEEK_SET);
  
  fseek(fpIn2, 0, SEEK_END);
  len2 =ftell(fpIn2);
  fseek(fpIn2, 0, SEEK_SET);
  //compare the file block by block
   if (len1 != len2) {
     fclose (fpIn1) ;
     fclose (fpIn2) ;
     return 0;
   } else {
     while (((iRead = fread (char1, 1, sizeof (char1)*multiple, fpIn1)) > 0) && ((iRead = fread (char2, 1, sizeof (char2)*multiple, fpIn2)) > 0)){ 
       if (strcmp(char1, char2)) {
	 return 0;
       }
     } 
     return 1;
   } 
}

