#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


const char **strings(char *language)
{
  static char *(text)[15];
  FILE *fp;
  size_t t=100;
  int i;
  char *newline_char;
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
    " whole package at https://github.com/41r0/TicTacToe-C\n");
    exit(0);
  }

  for(i=0;!feof(fp);i++){
    if(getline(&(text)[i],&t,fp)>0){
      newline_char=strpbrk(text[i],"\n");
      *newline_char=0;
      continue;
    }
  }
  return (const char**)text;
}

/*
 * This part of cose is responsible for loading .lang files
 * (those are written in plain text by the way). It is rather easy to translate
 * this game into your language as all you have to do is to include your
 * translation in check logic above (lines 14-38). I have also removed newlines
 * from strings because they have caused inconsistent behaviour with printf.
 */
