#include "../src/medium_operations.h"
#include <criterion/criterion.h>
#include <stdlib.h>

Test(variation,variation0)
{
  double t0[1]={0};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t0,1,out)==1);
  cr_assert(*out==0);
  free(out);
}

Test(variation,variation1)
{
  double t1[3]={1,3,5};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t1,3,out)==1);
  cr_assert(*out>=2.66&&*out<=2.67);
  free(out);
}

Test(variation,variation2)
{
  double t2[3]={4,-3,2};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t2,3,out)==1);
  cr_assert(*out==26.0/3);
  free(out);
}

Test(variation,variation3)
{
  double t3[5]={10.0,20.0,30.0,5.0,12.0};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t3,5,out)==1);
  cr_assert(*out>=76.640&&*out<=76.64000000001);
  free(out);
}

Test(variation,variation4)
{
  double t4[3]={5,7,9};
  double* out=malloc(sizeof(double));
  cr_assert(variation(t4,3,out)==1);
  cr_assert(*out==8.0/3);
  free(out);
}

Test(mean_absolute_deviation,m_ad1)
{
    double t1[5]={5,4,7,100,20};
    double *out=malloc(sizeof(double));
    cr_assert(mean_absolute_deviation(t1,5,out)==1);
    cr_assert(*out>=29.119999999&&*out<=29.12);
    free(out);
}

Test(mean_absolute_deviation,m_ad2)
{
  double t2[5]={2,2,3,4,14};
  double *out=malloc(sizeof(double));
  cr_assert(mean_absolute_deviation(t2,5,out)==1);
  cr_assert(*out==3.6);
  free(out);
}

Test(mean_absolute_deviation,m_ad3)
{
  double t3[8]={2900,3000,3200,3500,4400,4800,5000,5200};
  double* out=malloc(sizeof(double));
  cr_assert(mean_absolute_deviation(t3,8,out)==1);
  cr_assert(*out==850);
  free(out);
}

Test(standard_deviation,s_deviation0)
{
  double t0[2]={0,0};
  double *out=malloc(sizeof(double));
  cr_assert(standard_deviation(t0,2,out)==1);
  cr_assert(*out==0);
  free(out);
}

Test(coefficient_of_variation,cov0){
  double t0[3]={100,100,100};
  double *out=malloc(sizeof(double));
  cr_assert(coefficient_of_variation(t0,3,out)==1);
  cr_assert(*out==0);
  free(out);
}
