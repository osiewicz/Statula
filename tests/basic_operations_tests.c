#include <criterion/criterion.h>
#include "../src/basic_operations.h"
#include <stdio.h>
Test(mean,mean0)
{
  double t0[1]={0};
  cr_assert(mean(t0,1)==0);
}
Test(mean,mean1)
{
  double t1[3]={1,2,3};
  cr_assert(mean(t1,3)==2);
}
Test(mean,mean2)
{
  double t2[7]={1,-1,2,-2,3,-3,0};
  cr_assert(mean(t2,7)==0);
}
Test(mean,mean3)
{
  double t3[10]={3.2,7.0,120.3,11.234535,-14.33,0.0,1.333333,120000.3,-89.666};
  cr_assert(mean(t3,10)==12003.9371868);
}
Test(median,median0)
{
  double t0[1]={0.0};
  cr_assert(median(t0,1)==0.0);
}
Test(median,median1)
{
  double t1[2]={3.0,4.0};
  cr_assert(median(t1,2)==3.5);
}
Test(median,median2)
{
  double t2[3]={1.0,90.0,5.0};
  cr_assert(median(t2,3)==5.0);
}
Test(median,median3)
{
  double t3[7]={1,2,3,4,5,6,7};
  cr_assert(median(t3,7)==4.0);
}
Test(mode,mode0)
{
  double t0[7]={0};
  double* out;
  cr_assert(mode(t0,1,out)==1);
  cr_assert(*out==0.0);
}
Test(mode,mode1)
{
  double t1[3]={1.3,0,1.3};
  double* out;
  cr_assert(mode(t1,3,out)==1);
  cr_assert(*out==1.3);
}
Test(mode,mode2)
{
  double t2[4]={1.7,0,1.7,0};
  double* out;
  cr_assert(mode(t2,4,out)==-1);

}
Test(mode,mode3)
{
  double t3[10]={13934.88665,7.0,3.0,13.5,3.4,-5.3,1.2,-7.0,888.5,17.0};
  double* out;
  cr_assert(mode(t3,10,out)==-1);
}
Test(range,range0)
{
  double t0[1]={3};
  double *out;
  cr_assert(range(t0,1,out)==1);
  cr_assert(*out==0.0);
}
Test(range,range1)
{
  double t1[2]={3,-5.5};
  double *out;
  cr_assert(range(t1,2,out)==1);
  cr_assert(*out==8.5);
}
