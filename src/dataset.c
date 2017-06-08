#include "dataset.h"

static void quick_sort(double *arr, int elements)
{
	//  public-domain implementation by Darel Rex Finley.
	const int max_levels = 300;
	double piv;
	int beg[max_levels], end[max_levels], i=0, L, R, swap ;

	beg[0]=0;
	end[0]=elements;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv=arr[L];
			while (L<R) {
				while (arr[R]>=piv && L<R)
					R--;
				if (L<R)
					arr[L++]=arr[R];
				while (arr[L]<=piv && L<R)
					L++;
				if (L<R)
					arr[R--]=arr[L];
			}
			arr[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i]=L;
			i++;
      			if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
				swap=beg[i];
				beg[i]=beg[i-1];
				beg[i-1]=swap;

				swap=end[i];
				end[i]=end[i-1];
				end[i-1]=swap;
			}
		} else {
			i--;
		}
	}
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

	if(!set->numbers || set->number_count <= 0)
		return 0;
	return 1;
}

int free_dataset(struct dataset *set)
{
	free(set->numbers);
	return 1;
}

int compute_dataset(struct dataset *set)
{
	quick_sort(set->numbers,set->number_count);
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
	fprintf(stream,"\n--------\n%s %d\n%s %f\n%s %f\n%s ",text[0],
			set->number_count,text[1],(set->mean),text[2],(set->median),text[3]);
	if(set->is_mode_present!=1)
		fprintf(stream,"%s\n",text[11]);
	else
		fprintf(stream,"%f\n",(set->mode));
	fprintf(stream,"%s %f\n%s %f\n%s %f\n%s %f\n%s %.2f\%\n%s %f\n%s %f\n--------\n",
		text[4],(set->range),text[5],(set->central_moment),text[6],(set->standard_deviation),
		text[7], (set->mean_absolute_deviation),text[8],(set->coefficient_of_variation),
		text[9],(set->kurtosis),text[10],(set->skewness));

	return 1;
}
