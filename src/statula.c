#include "medium_operations.h"
#include "basic_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include "strings.c"
double* read_data(const char* source,int* num_count);
void print_help(const char**);
int main(int argc,char** argv)
{
  double *arr;
  int* num_count=malloc(sizeof(int));
  double* value=malloc(sizeof(double));
  char *filename=malloc(sizeof(char)*100);
  char *language=malloc(sizeof(char)*8);
  filename="data";
  language="en-gb";
    *num_count=0;
  if(argc>1){//Check for starting parameters
    for(int i=1;i<argc;i++){
      if(strncmp(argv[i],"--",2)==0){
        if(strcmp(argv[i],"--o")==0&&argc-i>1){
          if(strncmp(argv[i+1],"--",2)!=0)
            filename=argv[i+1];
        }
        else if(strcmp(argv[i],"--l")==0&&argc-i>1){
          if(strncmp(argv[i+1],"--",2)!=0)
            language=argv[i+1];
        }
      }
    }
  }
  const char** text=strings(language);
  if(argc>1){
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"--help")==0&&argc-i>0){
          print_help(text);
          return 0;
        }
    }
  }
  arr=read_data(filename,num_count);

  printf("%s\n%s\n%s %d\n%s %f\n%s %f\n%s ",text[0],text[1],text[2],*num_count,text[3],
  mean(arr,*num_count),text[4],median(arr,*num_count),text[5]);
  if(  mode(arr,*num_count,value)==-1)
    printf("%s\n%s ",text[13],text[6]);
  else
    printf("%f\n%s ",*value,text[6]);
  range(arr,*num_count,value);
  printf("%f\n%s ",*value,text[7]);
  central_moment(arr,*num_count,value,2);
  printf("%f\n%s ",*value,text[8]);
  standard_deviation(arr,*num_count,value);
  printf("%f\n%s ",*value,text[9]);
  mean_absolute_deviation(arr,*num_count,value);
  printf("%f\n%s ",*value,text[10]);
  coefficient_of_variation(arr,*num_count,value);
  printf("%.2f\%\n%s",*value,text[11]);
  kurtosis(arr,*num_count,value);
  printf("%f\n%s",*value,text[12]);
  skewness(arr,*num_count,value);
  printf("%f\n",*value);
  free(arr);
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
void print_help(const char** text)
{
  printf("Starting parameters:\n\
  --o * - open specified file\n\
  --l pl-pl/en-gb - change interface language\n\
  --help  - show help page\n ");
}
