#pragma once
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dataset.h>


int	mean(struct dataset *set);
int	median(struct dataset *set);
int	mode(struct dataset *set);
int	range(struct dataset *set);
long long int factorial(int n);
double cdf(double x);
