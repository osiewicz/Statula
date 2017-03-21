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
  double* value=malloc(sizeof(double));
  const char** text=strings("pl-pl");

  printf("%s\n%s\n%s%f\n%s%f\n%s",text[0],text[1],text[2],mean(arr,*num_count),
  text[3],median(arr,*num_count),text[4]);
  if(  mode(arr,*num_count,value)==-1)
    printf("%s\n%s",text[10],text[5]);
  else
    printf("%f\n%s",*value,text[5]);
  range(arr,*num_count,value);
  printf("%f\n%s",*value,text[6]);
  variation(arr,*num_count,value);
  printf("%f\n%s",*value,text[7]);
  standard_deviation(arr,*num_count,value);
  printf("%f\n%s",*value,text[8]);
  mean_absolute_deviation(arr,*num_count,value);
  printf("%f\n%s",*value,text[9]);
  coefficient_of_variation(arr,*num_count,value);
  printf("%.2f\%\n",*value);

  return 0;
}
double* read_data(const char* source,int* num_count)
{
  FILE *fp;
  if( access( source, F_OK ) != -1 ) {
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
  } else {
    printf("Specified file doesn't exists! Check whether you didn't make an error. Default data filename:data");
    exit(1);
  }
}
