#include "basic_operations.h"
#include "medium_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include "strings.h"



int init_dataset(struct dataset *set,const char *source);
int free_dataset(struct dataset *set);
double *read_data(const char *source,int *num_count);
void print_help(void);

static int compare (const void  *a, const void  *b)
{
	double _a = *(double*)a;
	double _b = *(double*)b;
	if(_a < _b) return -1;
	else if(_a == _b) return 0;
	else return 1;
}

int main(int argc,char **argv)
{
	char	*destination_file = malloc(sizeof(char)*150);
	char	*source_file = malloc(sizeof(char)*150);
	char	*language = malloc(sizeof(char)*8);
	char	mode_check = 0;
	char	file_save_check = 0;
	FILE	*save_file = NULL;
	double	*arr;
	double	mean_val, median_val, mode_val, range_val,central_moment_val, 
		standard_deviation_val,mean_absolute_deviation_val,
		coefficient_of_variation_val,kurtosis_val,skewness_val; 
	double	*value = malloc(sizeof(double));
	int	*num_count = malloc(sizeof(int));
//	struct dataset *p = malloc(sizeof(struct dataset));
//	printf("%d\n",	init_dataset(p,"01-big"));
//	free_dataset(p);
	source_file = "data";
	language = "en-gb";
	*num_count = 0;
	memset(destination_file,0,150);
  
	if(argc>1){//Check for starting parameters
		for(int i=1;i<argc;i++){
			if(strncmp(argv[i],"--",2)==0){
				if((strcmp(argv[i],"--help")==0||strcmp(argv[i],"--h")==0)&&argc-i>0){
					print_help();
					if(argc==2)
						return 0;
				} else if(strcmp(argv[i],"--o")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						source_file = argv[++i];
				} else if(strcmp(argv[i],"--l")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						language = argv[++i];
				} else if(strcmp(argv[i],"--s")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						destination_file = argv[++i];
					file_save_check = 1;
				} else {
					printf("\nInvalid starting parameter!\n\n");
					print_help();
					return -1;
				}
			} else if(argc==2) {
				source_file = argv[1];
			} else{
				print_help();
				return -1;
			}
		}
	}
	const char **text = strings(language);
	arr = read_data(source_file,num_count);

	qsort(arr,*num_count,sizeof(double),compare);
	mean_val = mean(arr,*num_count);
	median_val = median(arr,*num_count);
	mode_check = mode(arr,*num_count,&mode_val);
	range(arr,*num_count,&range_val);
	central_moment(arr,*num_count,&central_moment_val,2);
 	standard_deviation(arr,*num_count,&standard_deviation_val);
	mean_absolute_deviation(arr,*num_count,&mean_absolute_deviation_val);
	coefficient_of_variation(arr,*num_count,&coefficient_of_variation_val);
	kurtosis(arr,*num_count,&kurtosis_val);
	skewness(arr,*num_count,&skewness_val);
  
	printf("%s\n%s\n%s %d\n%s %f\n%s %f\n%s ",text[0],text[1],text[2],*num_count,text[3],mean_val,text[4],median_val,text[5]);
	if(mode_check==-1)
		printf("%s\n",text[13]);
	else
		printf("%f\n",mode_val);
	printf("%s %f\n%s %f\n%s %f\n%s %f\n%s %.2f\%\n%s %f\n%s %f\n",text[6],range_val,text[7],central_moment_val,text[8],standard_deviation_val,text[9],
		mean_absolute_deviation_val,text[10],coefficient_of_variation_val,text[11],kurtosis_val,text[12],skewness_val); 
	if(file_save_check==1){
		save_file = fopen(destination_file,"w");
		if(save_file){
			fprintf(save_file,"%s\n%s\n%s %d\n%s %f\n%s %f\n%s ",text[0],text[1],text[2],*num_count,text[3],mean_val,text[4],median_val,text[5]);
			if(mode_check==-1)
				fprintf(save_file,"%s\n",text[13]);
			else
				fprintf(save_file,"%f\n",mode_val);
			fprintf(save_file,"%s %f\n%s %f\n%s %f\n%s %f\n%s %.2f\%\n%s %f\n%s %f\n",
				text[6],range_val,text[7],central_moment_val,text[8],standard_deviation_val,
				text[9], mean_absolute_deviation_val,text[10],coefficient_of_variation_val,
				text[11],kurtosis_val,text[12],skewness_val); 
			fclose(save_file);
		} else {
			printf("Error opening a file for saving!");
		}
	}
	free(arr);
	free(value);
	free(num_count);

	return 0;
}

/*** dataset manipulation ***/

int init_dataset(struct dataset *set,const char *source)
{
	set->number_count = malloc(sizeof(int));
	set->is_mode_present = 0;
	set->numbers = read_data(source,set->number_count);
	set->mean = malloc(sizeof(double));
	set->median = malloc(sizeof(double));
	set->mode = malloc(sizeof(double));
	set->range = malloc(sizeof(double));
	set->central_moment = malloc(sizeof(double));
	set->standard_deviation = malloc(sizeof(double));
	set->mean_absolute_deviation = malloc(sizeof(double));
	set->coefficient_of_variation = malloc(sizeof(double));
	set->kurtosis = malloc(sizeof(double));
	set->skewness = malloc(sizeof(double));
	
	if(!set->number_count||!set->numbers||!set->mean||!set->median||!set->mode||!set->range
		||!set->central_moment||!set->standard_deviation||!set->mean_absolute_deviation
		||!set->coefficient_of_variation||!set->kurtosis||!set->skewness)
		return 0;
	return 1;
}

int free_dataset(struct dataset *set)
{
	free(set->number_count);
	free(set->numbers);
	free(set->mean);
	free(set->median);
	free(set->mode);
	free(set->range);
	free(set->central_moment);
	free(set->standard_deviation);
	free(set->mean_absolute_deviation);
	free(set->coefficient_of_variation);
	free(set->kurtosis);
	free(set->skewness);
	return 1;
}
/*** file manipulation ***/

double *read_data(const char* source,int* num_count)
{
	FILE *fp;
	if( access( source, F_OK ) != -1 ) {
		fp=fopen(source,"r");
		double dummy;
		for(int i=0;!feof(fp);i++){
			(*num_count)++;
			fscanf(fp," %lf ",&dummy);
		}
		double *numbers=malloc(sizeof(double)*(*num_count));
		rewind(fp);
		for(int i=0;!feof(fp);i++){
			fscanf(fp," %lf ",&numbers[i]);
		}
		fclose(fp);
		return numbers;
	} else {
		printf("Specified file doesn't exists! Check whether you didn't make an error. Default data filename:data");
		exit(1);
	}
}

void print_help(void)
{
	printf("Starting parameters:\n\
	--o * - open specified file\n\
	--l pl-pl/en-gb - change interface language\n\
	--help / --h - show help page\n\n");
}
