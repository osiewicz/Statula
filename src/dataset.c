#include "dataset.h"

static fpn *dataset_parse_default(char *buffer, int *num_count, fpn *numbers);

static void quick_sort(fpn *arr, int elements)
{
	//  public-domain implementation by Darel Rex Finley.
	const int max_levels = 300;
	fpn piv;
	int beg[max_levels], end[max_levels], i = 0, L, R, swap;

	beg[0] = 0;
	end[0] = elements;
	while (i >= 0) {
		L = beg[i];
		R = end[i] - 1;
		if (L < R) {
			piv = arr[L];
			while (L < R) {
				while (arr[R] >= piv && L < R) {
					R--;
				}
				if (L < R) {
					arr[L++] = arr[R];
				}
				while (arr[L] <= piv && L < R) {
					L++;
				}
				if (L < R) {
					arr[R--] = arr[L];
				}
			}
			arr[L] = piv;
			beg[i + 1] = L + 1;
			end[i + 1] = end[i];
			end[i] = L;
			i++;
			if (end[i] - beg[i] > end[i - 1] - beg[i - 1]) {
				swap = beg[i];
				beg[i] = beg[i - 1];
				beg[i - 1] = swap;

				swap = end[i];
				end[i] = end[i - 1];
				end[i - 1] = swap;
			}
		} else {
			i--;
		}
	}
}
static void set_defaults_dataset(struct dataset *set)
{
	set->number_count = 0;
	set->flags = 0;
	set->numbers = NULL;
	set->mean = 0;
	set->median = 0;
	set->mode = 0;
	set->range = 0;
	set->central_moment = 0;
	set->std_deviation = 0;
	set->m_abs_deviation = 0;
	set->coefficient_of_variation = 0;
	set->kurtosis = 0;
	set->skewness = 0;

}

int init_dataset(struct dataset *set, unsigned int flags, const char *source)
{

	set_defaults_dataset(set);
	set->flags = (flags & ~MODE_PRESENT);
	set->numbers = read_data(source, &(set->number_count), &dataset_parse_default);

	if (!set->numbers) {
		eprintf("init_dataset: Failed to allocate memory for data: ");
	}

	if (set->number_count <= 0) {
		eprintf("init_dataset: Invalid number count:");
	}
	return 0;
}

int free_dataset(struct dataset *set)
{
	free(set->numbers);
	set_defaults_dataset(set);
	return 0;
}

int compute_dataset(struct dataset *set)
{
	if ((set->flags & SORT) != 0) {
		quick_sort(set->numbers, set->number_count);
	}
	mean(set);
	median(set);
	mode(set);
	range(set);
	central_moment(set, 2);
	std_deviation(set);
	m_abs_deviation(set);
	coefficient_of_variation(set);
	kurtosis(set);
	skewness(set);
	return 0;
}

int print_dataset(struct dataset *set, FILE *stream, struct settings *settings,const char *dataset_name)
{
	if(settings->flags & PRINT_FILE_NAME){
		fprintf(stream,"%s",dataset_name==NULL?"Standard input":dataset_name);
	}
	fprintf(stream, "\n--------\n%s %d\n%s %.*f\n%s %.*f\n%s ", settings->text[0],
			set->number_count, settings->text[1], settings->precision, (set->mean), settings->text[2],
			settings->precision,(set->median), settings->text[3]);
	if ((set->flags & MODE_PRESENT)) {
		fprintf(stream, "%.*f\n",settings->precision, (set->mode));
	} else {
		fprintf(stream, "%s\n", settings->text[11]);
	}
	fprintf(stream, "%s %.*lf\n%s %.*lf\n%s %.*f\n%s %.*f\n%s %.*f\%\n%s %.*f\n%s %.*f\n--------\n",
			settings->text[4], settings->precision, (set->range), settings->text[5], settings->precision, (set->central_moment),
			settings->text[6], settings->precision, (set->std_deviation), settings->text[7], settings->precision, (set->m_abs_deviation),
			settings->text[8], settings->precision, (set->coefficient_of_variation),
			settings->text[9], settings->precision, (set->kurtosis), settings->text[10], settings->precision, (set->skewness));
	return 0;
}

static fpn *dataset_parse_default(char *buffer, int *num_count, fpn *numbers)
{
	static int memory_exp = 1;
	char *single_number = buffer;
	char *test = NULL;
	fpn dummy;
	fpn *temporary_pointer = NULL;
	if(buffer==NULL && num_count == NULL && numbers == NULL){
		memory_exp = 1;
		return NULL;
	}
	do {
		test = single_number;
		dummy = strtod(single_number, &single_number);
		if (test != single_number || dummy != 0.0) {
			if (memory_exp * BUFFER_SIZE <= (*num_count)) {
				memory_exp *= 2;
				temporary_pointer = realloc(numbers, sizeof(fpn) * BUFFER_SIZE * memory_exp);
				if (!temporary_pointer) {
					eprintf("read_data: Failed to reallocate memory for data array:");
				}
				numbers = temporary_pointer;
			}
			numbers[*num_count] = dummy;
			(*num_count)++;
		}
	} while (test != single_number);
	return (fpn *)numbers;
}
