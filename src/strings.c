#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "strings.h"

const char **strings(char *language)
{
  static char *(text)[15];
  FILE *fp;
  fp=check_lang_file(language);
  size_t t=100;
  int i;
  char *newline_char;

  for(i=0;!feof(fp);i++){
    if(getline(&(text)[i],&t,fp)>0){
      newline_char=strpbrk(text[i],"\n");
      *newline_char=0;
      continue;
    }
  }
  fclose(fp);
  return (const char**)text;
}
FILE* check_lang_file(char* language)
{
  FILE* fp;
  if(strcmp(language,"en-gb")==0){
    if( access( ".en-gb.lang", F_OK ) != -1 ) {
      fp=fopen(".en-gb.lang","r");
    } else {
      printf("Language pack for %s is missing!"
      " Consider using other language packs or download them from"
      " GitHub repository.",language);
      exit(0);
    }
  } else if(strcmp(language,"pl-pl")==0){
    if( access( ".pl-pl.lang", F_OK ) != -1 ) {
      fp=fopen(".pl-pl.lang","r");
    } else {
      printf("Language pack for %s is missing!"
      " Consider using other language packs or download them from"
      " GitHub repository.",language);
      exit(0);
    }
  } else{
    printf("Your package is corrupted! Please consider redownloading"
    " whole package at https://github.com/PiotrOsiewicz/Statula\n");
    exit(0);
  }
  return fp;
}
