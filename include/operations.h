#pragma once
#include <math.h>
#include <dataset.h>

int mean(struct dataset *set);
int median(struct dataset *set);
int mode(struct dataset *set);
int range(struct dataset *set);
int central_moment(struct dataset *set, int degree);
int std_deviation(struct dataset *set);
int m_abs_deviation(struct dataset *set);
int coefficient_of_variation(struct dataset *set);
int kurtosis(struct dataset *set);
int skewness(struct dataset *set);
