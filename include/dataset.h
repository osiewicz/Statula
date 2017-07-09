#pragma once

#ifdef REDUCED_PRECISION
typedef float fpn;
#else
typedef double fpn;
#endif
struct dataset
{
	int flags : 2;
	int number_count;
	fpn *numbers;
	fpn mean;
	fpn median;
	fpn mode;
	fpn range;
	fpn central_moment;
	fpn std_deviation;
	fpn m_abs_deviation;
	fpn coefficient_of_variation;
	fpn kurtosis;
	fpn skewness;
};

#define MODE_PRESENT (1 << 0)
#define SORT (1 << 1)

#include "operations.h"
#include "io.h"

int init_dataset(struct dataset *set, unsigned int flags, const char *source);
int free_dataset(struct dataset *set);
int compute_dataset(struct dataset *set);
int print_dataset(struct dataset *set, FILE *stream, const char **text);
