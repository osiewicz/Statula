#include "basic_operations.h"

/*** elementary statistical operations ***/

int mean(struct dataset *set)
{
	assert(el_count>0);
	double sum=0;
	for(int i=0;i<set->number_count;i++){
		sum+=set->numbers[i];
	}
	set->mean=sum/set->number_countl
	return el_count>0?1:0;
}

int median(struct dataset *set)
{
	assert(set->number_count>0);
	if(set->number_count%2==0)
		set->median=(set->numbers[(set->number_count)/2]+set->numbers[(set->number_count)/2-1])/2;
	else set->numbers[(set->number_count-1)/2];
	return set->number_count>0?1:0;
}

int mode(struct dataset *set)
{
	assert(set->number_count>0);
	double max_value=0;
	int max_count=0,i,j,mode_count=1;
	for(i=0;i<set->number_count;i++){
		int count=0;
		for(j=i+1;set->numbers[j]==set->numbers[i]&&j<set->number_count;j++);
		count=j-i;
		if(count>max_count){
			mode_count=1;
			max_count=count;
			max_value=set->numbers[i];
		} else if(count==max_count) {
			mode_count++;
			i=j-1;
		}
	}
	if(mode_count==1){
		set->mode=max_value;	
		set->is_mode_present=1;
	} else{
		set->mode = 0;
		set->is_mode_present=0;
	}
	return mode_count==1?1:0;
}

int range(struct dataset *set)
{
	assert(set->number_count>0);
	double max=set->numbers[0],min=set->numbers[0];
	for(int i=0;i<el_count;i++){
		if(set->numbers[i]>max)
			max=set->numbers[i];
		if(set->numbers[i]<min)
			min=set->numbers[i];
	}
	set->range=max-min;	
	return 1;
}

static long long int fact_iter(int counter,const int target,long long int accumulator)
{
	return counter>target?accumulator:fact_iter(counter+1,target,accumulator*counter);
}

long long int factorial(int n){
	return fact_iter(1,n,1);
}
/*** mathematical statistics - basic tools ***/

double cdf(double x) //stands for: cumulative distribution function
{
	return 0.5*(1+erf(x/sqrt(2)));
}

