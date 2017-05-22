#include "basic_operations.h"
#include "medium_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

int init_dataset(struct dataset *set,const char *source);
int free_dataset(struct dataset *set);
int compute_dataset(struct dataset *set);
int print_dataset(struct dataset *set,FILE* stream,const char **text);
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
	char	file_save_check = 0;
	FILE	*save_file = NULL;

	source_file = "data";
	language = "en-gb";
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
	struct dataset *set = malloc(sizeof(struct dataset));
	init_dataset(set,source_file);
	compute_dataset(set);
	
	const char **text = strings(language);
	print_dataset(set,stdout,text);

	if(file_save_check==1){
		save_file = fopen(destination_file,"w");
		if(save_file){
			print_dataset(set,save_file,text);
			fclose(save_file);
		} else {
			printf("Error opening a file for saving!");
		}
	}
	
	free_dataset(set);

	return 0;
}

/*** dataset manipulation ***/

int init_dataset(struct dataset *set,const char *source)
{
	set->number_count = 0;
	set->is_mode_present = 0;
	set->numbers = read_data(source,&(set->number_count));
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
			set->number_count,text[3],*(set->mean),text[4],*(set->median),text[5]);
	if(set->is_mode_present!=1)
		fprintf(stream,"%s\n",text[13]);
	else
		fprintf(stream,"%f\n",*(set->mode));
	fprintf(stream,"%s %f\n%s %f\n%s %f\n%s %f\n%s %.2f\%\n%s %f\n%s %f\n",
		text[6],*(set->range),text[7],*(set->central_moment),text[8],*(set->standard_deviation),
		text[9], *(set->mean_absolute_deviation),text[10],*(set->coefficient_of_variation),
		text[11],*(set->kurtosis),text[12],*(set->skewness)); 

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
	--s * - save result to specified file\n\
	--l pl-pl/en-gb - change interface language\n\
	--help / --h - show help page\n\n");
}
