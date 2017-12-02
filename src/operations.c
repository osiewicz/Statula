#include <operations.h>
#include <dataset.h>

static long long int fact_iter(int counter, const int target, long long int accumulator);

static double statula_pow(double base,unsigned long long exponent)
{
	double result = 1;
	while(exponent > 0){
		result *= base;
		exponent--;
	}
	return result;
}

int mean(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates mean for given dataset.
	 * Memory allocation responsibilities: None.
	 */
	
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"mean: NULL pointer passed :");
#endif
	}
	if(set->number_count < 1){
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_NULL,"mean: Invalid input : ");
#endif
	}
	long double sum = 0;
	for (int i = 0; i < set->number_count; i++) {
		sum += set->numbers[i];
	}
	set->mean = sum / set->number_count;
	return STATULA_SUCCESS;
}

int median(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates median for given dataset. Relies on dataset being sorted.
	 * Memory allocation responsibilities: None.
	 */
	
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"median: NULL pointer passed :");
#endif
	}
	if(set->number_count < 1){
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"median: Invalid input : ");
#endif
	}
	if (set->number_count % 2 == 0) {
		set->median = (set->numbers[(set->number_count) / 2] + set->numbers[(set->number_count) / 2 - 1]) / 2;
	} else {
		set->median = set->numbers[(set->number_count - 1) / 2];
	}
	return STATULA_SUCCESS;
}

int mode(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates mode for given dataset. Relies on dataset being sorted.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"mode: NULL pointer passed : ");
#endif
	}
	if(set->number_count == 0) {
		set->mode = 0;
		set->flags &= (~STATULA_MULTIPLE_MODES);
		set->flags |= STATULA_NO_MODE; 
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"mode: Invalid input : ");
#endif
	}
	
	double current_mode = 0;
	int max_count = 0, j, mode_count = 0;
	for (int i = 0; i < set->number_count; i++) {
		int count = 0;
		for (j = i + 1; j < set->number_count && set->numbers[j] == set->numbers[i]; j++)
			{ }
		count = j - i;
		if (count > max_count) {
			mode_count = 1;
			max_count = count;
			current_mode = set->numbers[i];
		} else if (count == max_count) {
			mode_count++;
		}
		i = j - 1;
	}
	if (mode_count == 1) {
		set->mode = current_mode;
		set->flags &= ~(STATULA_MULTIPLE_MODES);
		set->flags &= ~(STATULA_NO_MODE);
	} else {
		set->mode = 0;
		set->flags &= (~STATULA_NO_MODE);
		set->flags |= STATULA_MULTIPLE_MODES;
	}
	return STATULA_SUCCESS;
}

int range(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates range of given dataset.
	 * Memory allocation responsibilities: None.
	 */

	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"range: Invalid input:");
#endif
	}
	
	if (set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"range: Invalid input:");
#endif
	}
	double max = set->numbers[0];
	double min = set->numbers[0];
	for (int i = 0; i < set->number_count; i++) {
		if (set->numbers[i] > max) {
			max = set->numbers[i];
		} else if (set->numbers[i] < min) {
			min = set->numbers[i];
		}
	}
	set->range = fabs(max - min);
	return STATULA_SUCCESS;
}

int central_moment(struct dataset *set, int degree)
{
	/* Responsibilities:
	 * Calculates central moment of given degree for passed dataset.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"central_moment: NULL pointer passed : ");
#endif
	}
	if (set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"central_moment: Invalid input:");
#endif
	}
	if (degree < 1) {
		return STATULA_FAIL_GENERAL;
	}
	double c_moment = 0;
	
	for (int i = 0; i < set->number_count; i++) {
		c_moment += statula_pow((set->numbers[i] - set->mean), degree);
	}
	c_moment /= set->number_count;
	if (degree == 2) {
		set->central_moment = c_moment;
	} else if (degree == 4) {
		set->kurtosis = c_moment;
	}
	return STATULA_SUCCESS;
}

int std_deviation(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates standard deviation of given dataset.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"std_deviation: Invalid input:");
#endif
	}
	if (!set || set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"std_deviation: Invalid input:");
#endif
	}
	set->std_deviation = sqrt(set->central_moment);
	return STATULA_SUCCESS;
}

int m_abs_deviation(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates mean absolute deviation of given dataset.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"m_abs_deviation: NULL pointer passed :");
#endif
	}
	if (!set || set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"m_abs_deviation: Invalid input:");
#endif
	}
	double m_o_d = 0;
	for (int i = 0; i < set->number_count; i++) {
		m_o_d += fabs(set->numbers[i] - set->mean);
	}
	set->m_abs_deviation = m_o_d / set->number_count;
	return STATULA_SUCCESS;
}

int coefficient_of_variation(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates coefficient of variation for given dataset.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"coefficient_of_variation: NULL pointer passed :");
#endif
	}
	if (set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"coefficient_of_variation: Invalid input:");
#endif
	}
	if (set->mean == 0) {
		set->coefficient_of_variation = 0;
		return STATULA_FAIL_MATH;
	}
	set->coefficient_of_variation = (set->std_deviation / set->mean) * 100;
	return STATULA_SUCCESS;
}

int kurtosis(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates kurtosis of given dataset.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"kurtosis: NULL pointer passed :");
#endif
	}
	if (set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"kurtosis: Invalid input:");
#endif
	}
	central_moment(set, 4);
	if (set->std_deviation == 0) {
		return STATULA_FAIL_MATH;
	}
	set->kurtosis = set->kurtosis / statula_pow(set->std_deviation, 4) - 3;
	return STATULA_SUCCESS;
}

int skewness(struct dataset *set)
{
	/* Responsibilities:
	 * Calculates skewness of given dataset. Relies on dataset being sorted.
	 * Memory allocation responsibilities: None.
	 */
	if (!set) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		eprintf(STATULA_FAIL_NULL,"skewness: Invalid input:");
#endif
	}
	if (set->number_count < 1) {
#ifdef STATULA_TESTS
		return STATULA_FAIL_GENERAL;
#else
		eprintf(STATULA_FAIL_GENERAL,"skewness: Invalid input:");
#endif
	}
	if (set->std_deviation == 0) {
		return STATULA_FAIL_MATH;
	}
	set->skewness = 3 * ((set->mean - (set->median)) / (set->std_deviation));
	return (set->skewness <= 1 && set->skewness >= -1) ? STATULA_SUCCESS : STATULA_FAIL_MATH;
}

/*** Peripheral ***/

static long long int fact_iter(int counter, const int target, long long int accumulator)
{
	/* Responsibilities:
	 * Calculates factorial in an iterative manner.
	 * Memory allocation responsibilities: None.
	 */
	
	return counter > target ? accumulator : fact_iter(counter + 1, target, accumulator * counter);
}

long long int factorial(int n)
{
	/* Responsibilities:
	 * Calls fact_iter with proper parameters.
	 * Memory allocation responsibilities: None.
	 */
	
	return fact_iter(1, n, 1);
}
/*** mathematical statistics - basic tools ***/

double cdf(double x) //stands for: cumulative distribution function
{
	/* Responsibilities:
	 * Calculates cumulative distribution function for given x.
	 * Memory allocation responsibilities: None.
	 */
	
	return 0.5 * (1 + erf(x / sqrt(2)));
}
