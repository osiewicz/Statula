#include "basic_operations.h"

static int compare (const void * a, const void * b)
{
    double _a = *(double*)a;
    double _b = *(double*)b;
    if(_a < _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}

/*** elementary statistical operations ***/

double mean(double* array,int el_count)
{
  assert(el_count>0);
  double sum=0;
  for(int i=0;i<el_count;i++){
    sum+=array[i];
  }
  return sum/el_count;
}

double median(double* array,int el_count)
{
  assert(el_count>0);
  qsort(array,el_count,sizeof(double),compare);
  if(el_count%2==0)
    return (array[(el_count)/2]+array[(el_count)/2-1])/2;
  return array[(el_count-1)/2];
}
int mode(double* array, int el_count,double* output)
{
  assert(el_count>0);
  double max_value=0;
  int max_count=0,i,j,mode_count=1;
  qsort(array,el_count,sizeof(double),compare);
  for(i=0;i<el_count;i++){
    int count=0;
    for(j=i+1;array[j]==array[i]&&j<el_count;j++);
    count=j-i;
    if(count>max_count){
      mode_count=1;
      max_count=count;
      max_value=array[i];
    }
    else if(count==max_count)
      mode_count++;
        i=j-1;
  }
  if(mode_count==1){
    *output=max_value;
  }
  return mode_count==1?1:-1;
}
int range(double* array,int el_count,double *output)
{
  assert(el_count>0);
  double max=array[0],min=array[0];
  for(int i=0;i<el_count;i++){
    if(array[i]>max)
      max=array[i];
    if(array[i]<min)
      min=array[i];
  }
  *output=max-min;
  return 1;
}

static long long int fact_iter(int counter,const int target,long long int accumulator)
{
	return counter>target?accumulator:fact_iter(counter+1,target,accumulator*counter);
}
long long int factorial(int n){
	return fact_iter(1,n,1);
}
/*** mathematical statistics - basic tools ***/

double cdf(double x) //stands for: cumulative distribution function
{
	return 0.5*(1+erf(x/sqrt(2)));
}

