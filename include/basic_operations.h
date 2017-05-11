#ifndef BASICOPERATIONS
#define BASICOPERATIONS

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double mean(double* array,int el_count);
double median(double* array,int el_count);
int mode(double* array, int el_count,double* output);
int range(double* array,int el_count,double *output);
static long long int fact_iter(int counter,const int target,long long int accumulator);
long long int factorial(int n);
double cdf(double x);
#endif
