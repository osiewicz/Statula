#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "operations.h"
#include "io.h"
#include "dataset.h"
const char *progname = "tests";
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
	cr_assert(test->standard_deviation == 0);
	cr_assert(test->mean_absolute_deviation == 0);
	cr_assert(test->coefficient_of_variation == 0);
	free_dataset(test);
}

Test(dataset, 1)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, 0, "datasets/test_1");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert(test->mean == 3.5);
	cr_assert(test->median == 3.5);
	cr_assert((test->flags & MODE_PRESENT) == 0);
	cr_assert(test->range == 5);
	cr_assert_float_eq(test->central_moment, 2.91666, 0.0001);
	cr_assert_float_eq(test->standard_deviation, 1.70782512766, 0.0001);
	cr_assert(test->mean_absolute_deviation == 1.5);
	cr_assert_float_eq(test->coefficient_of_variation, 48.7950036474, 0.0001);
	cr_assert_float_eq(test->kurtosis, -1.2685, 0.0001);
	cr_assert_float_eq(test->skewness, 0, 0.0001);
	free_dataset(test);
}
