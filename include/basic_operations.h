#ifndef BASICOPERATIONS
#define BASICOPERATIONS

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct dataset{
	int	number_count;
	int	is_mode_present;
	double 	*numbers;
	double	*mean;
	double	*median;
	double	*mode;
	double	*range;
	double	*central_moment;
	double	*standard_deviation;
	double	*mean_absolute_deviation;
	double	*coefficient_of_variation;
	double	*kurtosis;
	double	*skewness;
};

int	mean(struct dataset *set);
int	median(struct dataset *set);
int	mode(struct dataset *set);
int	range(struct dataset *set);
static long long int fact_iter(int counter,const int target,long long int accumulator);
long long int factorial(int n);
double cdf(double x);
#endif
