#ifndef MEDIUMOPERATIONS
#define MEDIUMOPERATIONS
#include "basic_operations.h"
int central_moment(struct dataset *set,int degree);
int standard_deviation(struct dataset *set);
int mean_absolute_deviation(struct dataset *set);
int coefficient_of_variation(struct dataset *set);
int kurtosis(struct dataset *set);
int skewness(struct dataset *set);
#endif
