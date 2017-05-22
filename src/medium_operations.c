#include "medium_operations.h"

int central_moment(struct dataset *set,int degree)
{
	assert(set->number_count>0);
	double v_mean = set->mean;
	double var = 0;

	for(int i=0;i<set->number_count;i++){
		var += pow((set->numbers[i]-v_mean),degree);
	}
	var /= set->number_count;
	if(degree==2)
		set->central_moment=var;	
	else if(degree==4)
		set->kurtosis=var;
	return degree>1?1:0;
}

int standard_deviation(struct dataset *set)
{
	assert(set->number_count>0);
	set->standard_deviation=sqrt(set->central_moment);
	return 1;
}

int mean_absolute_deviation(struct dataset *set)
{
	double m_o_d = 0;

	for(int i=0;i<set->number_count;i++){
		m_o_d += fabs(set->numbers[i]-set->mean);
	}
	set->mean_absolute_deviation = m_o_d/set->number_count;
	return 1;
}

int coefficient_of_variation(struct dataset *set)
{
	if(mean_==0){
		set->coefficent_of_variation=0;
		return -1;
	}
	set->coefficient_of_variation=set->standard_deviation/((set->mean)*100);
	return 1;
}

int kurtosis(struct dataset *set)
{
	central_moment(set,4);
	set->kurtosis = set->kurtosis/pow(set->std_deviation,4)-3;
	return 1;
}

int skewness(struct dataset *set)
{
	set->skewness = 3*(set->mean-set->median)/(set->standard_deviation);
	return set->skewness<=1&&set->skewness>=-1?1:-1;
}
