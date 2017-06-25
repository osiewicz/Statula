#include "operations.h"

static long long int fact_iter(int counter, const int target, long long int accumulator);

int mean(struct dataset *set)
{
	if (set->number_count < 1)
		return 1;
	long double sum = 0;
	for (int i = 0; i < set->number_count; i++)
	{
		sum += set->numbers[i];
	}
	set->mean = sum / set->number_count;
	return 0;
}

int median(struct dataset *set)
{
	if (set->number_count < 1)
		return 1;
	if (set->number_count % 2 == 0)
		set->median = (set->numbers[(set->number_count) / 2] + set->numbers[(set->number_count) / 2 - 1]) / 2;
	else
		set->median = set->numbers[(set->number_count - 1) / 2];
	return 0;
}

int mode(struct dataset *set)
{
	double current_mode = 0;
	int max_count = 0, j, mode_count = 0;
	for (int i = 0; i + max_count - 1 < set->number_count; i++)
	{
		int count = 0;
		for (j = i + 1; j < set->number_count && set->numbers[j] == set->numbers[i]; j++)
			;
		count = j - i;
		if (count > max_count)
		{
			mode_count = 1;
			max_count = count;
			current_mode = set->numbers[i];
		}
		else if (count == max_count)
		{
			mode_count++;
		}
		i = j - 1;
	}
	if (mode_count == 1)
	{
		set->mode = current_mode;
		set->flags |= MODE_PRESENT;
	}
	else
	{
		set->mode = 0;
		set->flags &= ~MODE_PRESENT;
	}
	return mode_count == 1 ? 0 : 1;
}

int range(struct dataset *set)
{
	double max = set->numbers[0];
	double min = set->numbers[0];
	for (int i = 0; i < set->number_count; i++)
	{
		if (set->numbers[i] > max)
			max = set->numbers[i];
		else if (set->numbers[i] < min)
			min = set->numbers[i];
	}
	set->range = fabs(max - min);
	return 0;
}

int central_moment(struct dataset *set, int degree)
{
	if (degree < 1)
		return 1;
	double c_moment = 0;

	for (int i = 0; i < set->number_count; i++)
	{
		c_moment += pow((set->numbers[i] - set->mean), degree);
	}
	c_moment /= set->number_count;
	if (degree == 2)
		set->central_moment = c_moment;
	else if (degree == 4)
		set->kurtosis = c_moment;
	return 0;
}

int standard_deviation(struct dataset *set)
{
	set->standard_deviation = sqrt(set->central_moment);
	return 0;
}

int mean_absolute_deviation(struct dataset *set)
{
	double m_o_d = 0;

	for (int i = 0; i < set->number_count; i++)
	{
		m_o_d += fabs(set->numbers[i] - set->mean);
	}
	set->mean_absolute_deviation = m_o_d / set->number_count;
	return 0;
}

int coefficient_of_variation(struct dataset *set)
{
	if (set->mean == 0)
	{
		set->coefficient_of_variation = 0;
		return 1;
	}
	set->coefficient_of_variation = (set->standard_deviation / set->mean) * 100;
	return 0;
}

int kurtosis(struct dataset *set)
{
	central_moment(set, 4);
	if (set->standard_deviation == 0)
		return 1;
	set->kurtosis = set->kurtosis / pow(set->standard_deviation, 4) - 3;
	return 0;
}

int skewness(struct dataset *set)
{
	if (set->standard_deviation == 0)
		return 1;
	set->skewness = 3 * ((set->mean - (set->median)) / (set->standard_deviation));
	return !(set->skewness <= 1 && set->skewness >= -1);
}

/*** Peripheral ***/

static long long int fact_iter(int counter, const int target, long long int accumulator)
{
	return counter > target ? accumulator : fact_iter(counter + 1, target, accumulator * counter);
}

long long int factorial(int n)
{
	return fact_iter(1, n, 1);
}
/*** mathematical statistics - basic tools ***/

double cdf(double x) //stands for: cumulative distribution function
{
	return 0.5 * (1 + erf(x / sqrt(2)));
}
