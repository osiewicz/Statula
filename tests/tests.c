#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <operations.h>
#include <io.h>
#include <dataset.h>
#include <misc.h>

const char *progname = "tests";
const double epsilon = 0.0001;

/* General functionality test */

Test(dataset, 0s)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, STATULA_SORT, "datasets/test_0");
	compute_dataset(test);
	cr_assert(test->number_count == 1);
	cr_assert(test->mean == 0);
	cr_assert((test->flags & (STATULA_MULTIPLE_MODES | STATULA_NO_MODE)) == 0);
	cr_assert(test->range == 0);
	cr_assert(test->central_moment == 0);
	cr_assert(test->std_deviation == 0);
	cr_assert(test->m_abs_deviation == 0);
	cr_assert(test->coefficient_of_variation == 0);
	cr_assert(test->kurtosis == 0);
	free_dataset(test);
}

Test(dataset, 0)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, 0, "datasets/test_0");
	compute_dataset(test);
	cr_assert(test->number_count == 1);
	cr_assert(test->mean == 0);
	cr_assert(test->median == 0);
	cr_assert((test->flags & (STATULA_MULTIPLE_MODES | STATULA_NO_MODE)) == 0);
	cr_assert(test->mode == 0);
	cr_assert(test->range == 0);
	cr_assert(test->central_moment == 0);
	cr_assert(test->std_deviation == 0);
	cr_assert(test->m_abs_deviation == 0);
	cr_assert(test->coefficient_of_variation == 0);
	cr_assert(test->kurtosis == 0);
	cr_assert(test->skewness == 0);
	free_dataset(test);
}

Test(dataset, 1s)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, STATULA_SORT, "datasets/test_1");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert(test->mean == 3.5);
	cr_assert(test->median == 3.5);
	cr_assert((test->flags & STATULA_MULTIPLE_MODES) != 0);
	cr_assert(test->range == 5);
	cr_assert_float_eq(test->central_moment, 2.91666, epsilon);
	cr_assert_float_eq(test->std_deviation, 1.70782512766, epsilon);
	cr_assert(test->m_abs_deviation == 1.5);
	cr_assert_float_eq(test->coefficient_of_variation, 48.7950036474, epsilon);
	cr_assert_float_eq(test->kurtosis, -1.2685, epsilon);
	cr_assert_float_eq(test->skewness, 0, epsilon);
	free_dataset(test);
}

Test(dataset, 1)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, 0, "datasets/test_1");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert(test->mean == 3.5);
	cr_assert(test->range == 5);
	cr_assert_float_eq(test->central_moment, 2.91666, epsilon);
	cr_assert_float_eq(test->std_deviation, 1.70782512766, epsilon);
	cr_assert(test->m_abs_deviation == 1.5);
	cr_assert_float_eq(test->coefficient_of_variation, 48.7950036474, epsilon);
	cr_assert_float_eq(test->kurtosis, -1.2685, epsilon);
	free_dataset(test);
}

Test(dataset,2s)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, STATULA_SORT, "datasets/test_2");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert_float_eq(test->mean, 137.528, epsilon);
	cr_assert_float_eq(test->median, 4.2, epsilon);
	cr_assert((test->flags & (STATULA_MULTIPLE_MODES | STATULA_NO_MODE)) == 0);
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

Test(dataset,2)
{
	struct dataset *test = malloc(sizeof(struct dataset));
	init_dataset(test, STATULA_SORT, "datasets/test_2");
	compute_dataset(test);
	cr_assert(test->number_count == 6);
	cr_assert_float_eq(test->mean, 137.528, epsilon);
	cr_assert_float_eq(test->range, 771.768, epsilon);
	cr_assert_float_eq(test->central_moment, 80010.96886, epsilon);
	cr_assert_float_eq(test->std_deviation, 282.8621022, epsilon);
	cr_assert_float_eq(test->m_abs_deviation, 210.413333, epsilon);
	cr_assert_float_eq(test->coefficient_of_variation, 205.6760094, epsilon);
	cr_assert_float_eq(test->kurtosis, 1.170773766, epsilon);
	free_dataset(test);
}

/* io.c tests */

Test(load_strings,MissingFile)
{
	int mock_count = 0;
	cr_assert(load_strings("ThatsNotInThisFolder",&mock_count) == NULL);
	cr_assert(load_strings(NULL,&mock_count) == 0);
	cr_assert(load_strings("NotInAFolder",NULL) == 0);
}

Test(init_strings,ProperFile)
{
	struct strings *test = init_strings("en-gb");
	cr_assert(test != NULL);
	free_strings(test);
}

Test(read_data,MissingFile)
{
	unsigned long long mock_count = 0;
	
	cr_assert(read_data("ThatsNotInThisFolder", &mock_count, &dataset_parse_default) == NULL);
}

Test(free_strings,NULLptr)
{
	cr_assert(free_strings(NULL) == -1);
}

/* dataset.c tests */

Test(init_dataset,NULLptr)
{
	cr_assert(init_dataset(NULL,0,"ThatsNotInThisFolder") == STATULA_FAIL_NULL);
}

Test(init_dataset,EmptySet)
{
	struct dataset *mock = malloc(sizeof(struct dataset));
	cr_assert(init_dataset(mock, 0,"datasets/test_3") == STATULA_FAIL_MATH);
	free(mock);
}

Test(print_dataset,NULLptr)
{
	cr_assert(print_dataset(NULL,NULL,NULL,NULL) == STATULA_FAIL_NULL);
}

/* misc.c tests */

Test(enable_stdin,NULLptr)
{
	cr_assert(enable_stdin(NULL) == STATULA_FAIL_NULL);
}

Test(parse_cmd_args,NULLptr)
{
	char **mock = malloc(sizeof(char*));
	cr_assert(parse_cmd_args(2,NULL) == NULL);
	cr_assert(parse_cmd_args(-5,mock) == NULL);
	free(mock);
}

Test(parse_cmd_args,Valid1)
{
	char **mock = malloc(sizeof(char*));
	mock[0] = malloc(sizeof(char)*5);
	strcpy(mock[0],"Test");
	mock[0][4] = '\0';
	struct settings *settings = parse_cmd_args(1,mock);
	cr_assert(settings != NULL);
	cr_assert((settings->flags & STATULA_STDIN) != 0);
	free(mock[0]);
	free(mock);
	free_settings(settings);
}

Test(parse_cmd_args,ValidDefaultName)
{
	char **mock = malloc(sizeof(char*)*2);
	mock[0] = malloc(sizeof(char)*5);
	strcpy(mock[0],"./wh");
	mock[0][4] = '\0';
	mock[1] = malloc(sizeof(char)*16);
	strcpy(mock[1],"datasets/test_0");
	mock[1][15]='\0';
	struct settings *settings = parse_cmd_args(2,mock);
	cr_assert(settings != NULL);
	cr_assert(settings->in_file_count == 1);
	
	for(int i=0;i<2;i++){
		free(mock[i]);
	}
	free(mock);
	free_settings(settings);
}

Test(is_valid_parameter,Suite)
{
	cr_assert(is_valid_parameter(NULL,NULL,NULL) == 0);
	cr_assert(is_valid_parameter("-l","--language","-l") == 1);
	cr_assert(is_valid_parameter("--aw","--aw","-a") == 1);
}

Test(is_argument,Suite)
{
	cr_assert(is_argument(NULL) == 0);
	cr_assert(is_argument("-l") == 0);
	cr_assert(is_argument("test") == 1);
}

Test(eprintf,NULLptr)
{
//	cr_assert(eprintf(NULL) == 1);
}
