#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "operations.h"
#include "io.h"
#include "dataset.h"
const char *progname = "tests";
const double epsilon = 0.0001;
Test(dataset, 0)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, 0, "datasets/test_0");
	compute_dataset(test);
	cr_assert(test->number_count == 1);
	cr_assert(test->mean == 0);
	cr_assert(test->median == 0);
	cr_assert((test->flags & MODE_PRESENT) != 0);
	cr_assert(test->mode == 0);
	cr_assert(test->range == 0);
	cr_assert(test->central_moment == 0);
	cr_assert(test->std_deviation == 0);
	cr_assert(test->m_abs_deviation == 0);
	cr_assert(test->coefficient_of_variation == 0);
	free_dataset(test);
}

Test(dataset, 1)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, SORT, "datasets/test_1");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert(test->mean == 3.5);
	cr_assert(test->median == 3.5);
	cr_assert((test->flags & MODE_PRESENT) == 0);
	cr_assert(test->range == 5);
	cr_assert_float_eq(test->central_moment, 2.91666, epsilon);
	cr_assert_float_eq(test->std_deviation, 1.70782512766, epsilon);
	cr_assert(test->m_abs_deviation == 1.5);
	cr_assert_float_eq(test->coefficient_of_variation, 48.7950036474, epsilon);
	cr_assert_float_eq(test->kurtosis, -1.2685, epsilon);
	cr_assert_float_eq(test->skewness, 0, epsilon);
	free_dataset(test);
}
Test(dataset,2)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, SORT, "datasets/test_2");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert_float_eq(test->mean, 137.528, epsilon);
	cr_assert_float_eq(test->median, 4.2, epsilon);
	cr_assert((test->flags & MODE_PRESENT) == 1);
	cr_assert_float_eq(test->mode, 4.2, epsilon);
	cr_assert_float_eq(test->range, 771.768, epsilon);
	cr_assert_float_eq(test->central_moment, 80010.96886, epsilon);
	cr_assert_float_eq(test->std_deviation, 282.8621022, epsilon);
	cr_assert_float_eq(test->m_abs_deviation, 210.413333, epsilon);
	cr_assert_float_eq(test->coefficient_of_variation, 205.6760094, epsilon);
	cr_assert_float_eq(test->kurtosis, 1.170773766, epsilon);
	cr_assert_float_eq(test->skewness, 1.414060066 , epsilon);
	free_dataset(test);
}
