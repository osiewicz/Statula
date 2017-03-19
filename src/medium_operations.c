#include "basic_operations.h"
#include "medium_operations.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int variation(double* arr,int el_count,double* output)
{
  assert(el_count>0);
  double v_mean=mean(arr,el_count);
  double var=0;
  for(int i=0;i<el_count;i++){
    var+=pow((arr[i]-v_mean),2);
  }
  var/=el_count;
  *output=var;
  return 1;
}
int standard_deviation(double* arr,int el_count,double* output)
{
  assert(el_count>0);
  double *var=malloc(sizeof(double));
  variation(arr,el_count,var);
    *output=pow(*var,0.5);
  return 1;
}
int mean_ordinary_deviation(double* arr,int el_count,double* output)
{
  double m_o_d=0;
  double a_mean=mean(arr,el_count);
  for(int i=0;i<el_count;i++){
    m_o_d+=fabs(arr[i]-a_mean);
  }
  *output=m_o_d/el_count;
  return 1;
}
