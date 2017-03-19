#include "medium_operations.h"
#include "basic_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include "strings.c"
double* read_data(const char* source,int* num_count);
int main(int argc,char** argv)
{
  double *arr;
  char *filename=malloc(sizeof(char)*100);
  if(argc<2)
    filename="data";
  else
    filename=argv[1];
  int* num_count=malloc(sizeof(int));
  *num_count=0;
  arr=read_data(filename,num_count);
  double* test=malloc(sizeof(double));
  const char** text=strings("pl-pl");
  printf("%s\n%s\n%s%f\n%s",text[0],text[1],text[2],mean(arr,*num_count),text[7]);
  standard_deviation(arr,*num_count,test);
  printf("%f",*test);
  return 0;
}
double* read_data(const char* source,int* num_count)
{
  FILE *fp;
  fp=fopen(source,"r");
  double dummy;
  for(int i=0;!feof(fp);i++){
    (*num_count)++;
    fscanf(fp," %lf ",&dummy);
  }
  double* numbers=malloc(sizeof(double)*(*num_count));
  rewind(fp);
  for(int i=0;!feof(fp);i++){
    fscanf(fp," %lf ",&numbers[i]);
  }
  fclose(fp);
  return numbers;
}
