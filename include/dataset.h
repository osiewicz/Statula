#pragma once

struct dataset{
	int	flags : 2;
	int	number_count;
	double 	*numbers;
	double	mean;
	double	median;
	double	mode;
	double	range;
	double	central_moment;
	double	standard_deviation;
	double	mean_absolute_deviation;
	double	coefficient_of_variation;
	double	kurtosis;
	double	skewness;
};

#define	MODE_PRESENT (1<<0)
#define	SORT (1<<1)

#include "basic_operations.h"
#include "medium_operations.h"
#include "io.h"

int init_dataset(struct dataset *set,unsigned int flags, const char *source);
int free_dataset(struct dataset *set);
int compute_dataset(struct dataset *set);
int print_dataset(struct dataset *set,FILE* stream,const char **text);
