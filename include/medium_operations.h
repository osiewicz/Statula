#ifndef MEDIUMOPERATIONS
#define MEDIUMOPERATIONS
#include "basic_operations.h"
int central_moment(double* arr,int el_count,double* output,int degree);
int standard_deviation(double* arr,int el_count,double* output);
int mean_absolute_deviation(double* arr,int el_count,double* output);
int coefficient_of_variation(double* arr,int el_count,double* output);
int kurtosis(double* arr,int el_count,double* output);
int skewness(double* arr,int el_count,double* output);
#endif
