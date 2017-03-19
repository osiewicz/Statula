#include "../src/medium_operations.h"
#include <criterion/criterion.h>
#include <stdlib.h>
Test(variation,variation0)
{
  double t0[1]={0};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t0,1,out)==1);
  cr_assert(*out==0);
}
Test(variation,variation1)
{
  double t1[3]={1,3,5};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t1,3,out)==1);
  cr_assert(*out>=2.66&&*out<=2.67);
}
Test(variation,variation3)
{
  double t2[5]={10.0,20.0,30.0,5.0,12.0};
  double *out=malloc(sizeof(double));
  cr_assert(variation(t2,5,out)==1);
  cr_assert(*out>=76.640&&*out<=76.64000000001);
}
Test(mean_ordinary_deviation,m_od1)
{
    double t1[5]={5,4,7,100,20};
    double *out=malloc(sizeof(double));
    cr_assert(mean_ordinary_deviation(t1,5,out)==1);
    cr_assert(*out>=29.119999999&&*out<=29.12);
}
Test(standard_deviation,s_deviation0)
{
  double t0[2]={0,0};
  double *out=malloc(sizeof(double));
  cr_assert(standard_deviation(t0,2,out)==1);
  cr_assert(*out==0);
}
