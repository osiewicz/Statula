#include "basic_operations.h"
#include "medium_operations.h"
#include <math.h>

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
