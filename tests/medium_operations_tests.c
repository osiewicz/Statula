#include "../src/medium_operations.h"
#include <criterion/criterion.h>
Test(variation,variation0)
{
  double t0[1]={0};
  double *out;
  cr_assert(variation(t0,1,out)==1);
  cr_assert(*out==0);
}
Test(variation,variation1)
{
  double t1[3]={1,3,5};
  double *out;
  cr_assert(variation(t1,3,out)==1);
  cr_assert(*out>=2.66&&*out<=2.67);
}
Test(variation,variation3)
{
  double t2[5]={10.0,20.0,30.0,5.0,12.0};
  double *out;
  cr_assert(variation(t2,5,out)==1);
  cr_assert(*out>=76.640&&*out<=76.6401);
}
