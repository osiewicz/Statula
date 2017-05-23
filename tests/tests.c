#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "medium_operations.h"
#include "io.h"
#include "dataset.h"

Test(dataset,0)
{
	struct dataset *test=malloc(sizeof(struct dataset));
	init_dataset(test,"datasets/test_0");
	compute_dataset(test);
	cr_assert(test->number_count==1);
	cr_assert(*(test->mean) == 0);
	cr_assert(*(test->median)==0);
	cr_assert(test->is_mode_present==1);
	cr_assert(*(test->mode)==0);
	cr_assert(*(test->range)==0);
	cr_assert(*(test->central_moment)==0);
	cr_assert(*(test->standard_deviation)==0);
	cr_assert(*(test->mean_absolute_deviation)==0);
	cr_assert(*(test->coefficient_of_variation)==0);
	free_dataset(test);
}
