#include "dataset.h"

static int compare (const void  *a, const void  *b)
{
	double _a = *(double*)a;
	double _b = *(double*)b;
	if(_a < _b) return -1;
	else if(_a == _b) return 0;
	else return 1;
}

int init_dataset(struct dataset *set,const char *source)
{
	set->number_count = 0;
	set->is_mode_present = 0;
	set->numbers = read_data(source,&(set->number_count));
	set->mean = 0;
	set->median = 0; 
	set->mode = 0; 
	set->range = 0; 
	set->central_moment = 0;
	set->standard_deviation = 0;
	set->mean_absolute_deviation = 0;
	set->coefficient_of_variation = 0;
	set->kurtosis = 0;
	set->skewness = 0;

	if(!set->numbers)
		return 0;
	return 1;
}

int free_dataset(struct dataset *set)
{
	free(set->numbers);
	free(set);
	return 1;
}

int compute_dataset(struct dataset *set)
{
	qsort(set->numbers,(set->number_count),sizeof(double),compare);
	mean(set);
	median(set);
	mode(set);
	range(set);
	central_moment(set,2);
	standard_deviation(set);
	mean_absolute_deviation(set);
	coefficient_of_variation(set);
	kurtosis(set);
	skewness(set);
	return 1;
}

int print_dataset(struct dataset *set,FILE* stream,const char** text)
{
	fprintf(stream,"%s\n%s\n%s %d\n%s %f\n%s %f\n%s ",text[0],text[1],text[2],
			set->number_count,text[3],(set->mean),text[4],(set->median),text[5]);
	if(set->is_mode_present!=1)
		fprintf(stream,"%s\n",text[13]);
	else
		fprintf(stream,"%f\n",(set->mode));
	fprintf(stream,"%s %f\n%s %f\n%s %f\n%s %f\n%s %.2f\%\n%s %f\n%s %f\n",
		text[6],(set->range),text[7],(set->central_moment),text[8],(set->standard_deviation),
		text[9], (set->mean_absolute_deviation),text[10],(set->coefficient_of_variation),
		text[11],(set->kurtosis),text[12],(set->skewness));

	return 1;
}
