#pragma once

#ifdef STATULA_REDUCED_PRECISION
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

#define STATULA_MODE_PRESENT (1 << 0)
#define STATULA_SORT (1 << 1)

#include <misc.h>
#include <operations.h>
#include <io.h>

int init_dataset(struct dataset *set, unsigned int flags, const char *source);
int free_dataset(struct dataset *set);
int compute_dataset(struct dataset *set);
int print_dataset(struct dataset *set, FILE *stream, struct settings *settings,const char *dataset_name);
fpn *dataset_parse_default(char *buffer, int *num_count, fpn *numbers);
