#include "basic_operations.h"

/*** elementary statistical operations ***/

int mean(struct dataset *set)
{
	assert(set->number_count > 0);
	double sum  =  0;
	for(int i  =  0 ; i < set->number_count ; i++){
		sum +=  set->numbers[i];
	}
	set->mean  =  sum / set->number_count;
	return set->number_count > 0 ? 1 : 0;
}

int median(struct dataset *set)
{
	assert(set->number_count > 0);
	if(set->number_count%2 == 0)
		set->median = (set->numbers[(set->number_count) / 2] + set->numbers[(set->number_count) / 2 - 1]) / 2;
	else
		set->median = set->numbers[(set->number_count - 1) / 2];
	return set->number_count > 0 ? 1 : 0 ;
}

int mode(struct dataset *set)
{
	assert(set->number_count > 0);
	double current_mode = 0;
	int max_count = 0,j,mode_count = 1;
	for(int i = 0;i + max_count < set->number_count;i++){
		int count = 0;
		for(j = i+1;j<set->number_count && set->numbers[j] == set->numbers[i];j++);
		count = j-i;
		if(count > max_count){
			mode_count = 1;
			max_count = count;
			current_mode = set->numbers[i];
		} else if(count == max_count) {
			mode_count++;
		}
		i = j-1;
	}
	if(mode_count == 1){
		set->mode = current_mode;	
		set->is_mode_present = 1;
	} else{
		set->mode = 0;
		set->is_mode_present = 0;
	}
	return mode_count == 1 ? 1 : 0;
}

int range(struct dataset *set)
{
	assert(set->number_count > 0);
	double max = set->numbers[0];
	double min = set->numbers[0];
	for(int i = 0;i < set->number_count ; i++){
		if(set->numbers[i] > max)
			max = set->numbers[i];
		else if(set->numbers[i] < min)
			min = set->numbers[i];
	}
	set->range = fabs(max-min);	
	return 1;
}

/*** Peripheral ***/

static long long int fact_iter(int counter,const int target,long long int accumulator)
{
	return counter > target ? accumulator : fact_iter(counter+1 , target , accumulator * counter);
}

long long int factorial(int n){
	return fact_iter(1,n,1);
}
/*** mathematical statistics - basic tools ***/

double cdf(double x) //stands for: cumulative distribution function
{
	return 0.5 * (1 + erf(x / sqrt(2)));
}

