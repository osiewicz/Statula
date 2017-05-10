#include "medium_operations.h"
int central_moment(double* arr,int el_count,double* output,int degree)
{
  assert(el_count>0);
  double v_mean=mean(arr,el_count);
  double var=0;
  for(int i=0;i<el_count;i++){
    var+=pow((arr[i]-v_mean),degree);
  }
  var/=el_count;
  *output=var;
  return 1;
}
int standard_deviation(double* arr,int el_count,double* output)
{
  assert(el_count>0);
  double *var=malloc(sizeof(double));
  central_moment(arr,el_count,var,2);
    *output=pow(*var,0.5);
  free(var);
  return 1;
}
int mean_absolute_deviation(double* arr,int el_count,double* output)
{
  double m_o_d=0;
  double a_mean=mean(arr,el_count);
  for(int i=0;i<el_count;i++){
    m_o_d+=fabs(arr[i]-a_mean);
  }
  *output=m_o_d/el_count;
  return 1;
}
int coefficient_of_variation(double* arr, int el_count,double* output)
{
  double *std_deviation=malloc(sizeof(double));
  standard_deviation(arr,el_count,std_deviation);
  double mean_=mean(arr,el_count);
  if(mean_==0){
    *output=0;
    return -1;
  }
  (*output)=(*std_deviation)/mean_*100;
  free(std_deviation);
  return 1;
}
int kurtosis(double* arr,int el_count,double* output)
{
  double *c_moment=malloc(sizeof(double));
  central_moment(arr,el_count,c_moment,4);
  double *std_deviation=malloc(sizeof(double));
  standard_deviation(arr,el_count,std_deviation);
  *output=*c_moment/pow(*std_deviation,4)-3;
  free(c_moment);
  return 1;
}
int skewness(double* arr,int el_count,double* output)
{
  double median_=median(arr,el_count);
  double mean_=mean(arr,el_count);
  double *std_deviation=malloc(sizeof(double));
  standard_deviation(arr,el_count,std_deviation);
  *output=3*(mean_-median_)/(*std_deviation);
  free(std_deviation);
  return *output<=1&&*output>=-1?1:-1;
}
