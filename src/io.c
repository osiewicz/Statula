#include "io.h"

/*** loading strings from files ***/

const char **strings(char *language)
{
	static char *(text)[MAX_LINE_COUNT];
	char *newline_char;
	FILE *fp;
	size_t max_line_size=100;
	fp=open_lang_file(language);
	if(!fp){
		printf("Could not open file .%s.lang.\n",language);
		exit(0);
	}
	for(int i=0;i<MAX_LINE_COUNT && !feof(fp);i++){
		if(getline(&(text)[i],&max_line_size,fp)>0){
			newline_char=strpbrk(text[i],"\n");
			*newline_char=0;
		}
	}
	fclose(fp);
	return (const char**)text;
}

FILE* open_lang_file(const char* language)
{
	FILE* fp;
	char *filename = malloc(sizeof(char)*(strlen(language)+7));
	filename[0]='.';
	memcpy(filename+1,language,strlen(language));
	strncat(filename+strlen(language),".lang",5);
	if( access( filename, F_OK ) != -1 ) {
		fp=fopen(filename,"r");
	} else {
		printf("Language pack for %s is missing!"
		" Consider using other language packs or download them from"
		" GitHub repository.",language);
		exit(1);
	}
	return fp;
}

/*** read data from file ***/

double *read_data(const char* source,int* num_count)
{
	if( access( source, F_OK ) != -1 ) {
		FILE *fp;
		char *buffer = malloc(sizeof(char)*BUFFER_SIZE);
		if(!buffer){
			puts("Error allocating memory for line buffer");
			exit(1);
		}
		fp=fopen(source,"r");
		if(fp){
			double	dummy;
			size_t	size = BUFFER_SIZE;
			int	memory_exp = 1;
			char	*single_number = NULL;
			char	*test = NULL;
			double	*numbers=malloc(sizeof(double)*BUFFER_SIZE*memory_exp);
			if(!numbers){
				puts("Error allocating memory for data array");
				exit(1);
			}
			for(int i=0;!feof(fp);){
				if(getline(&buffer,&size,fp)>0){
					single_number = buffer; 
					do{
						test = single_number;
						dummy = strtod(single_number,&single_number);
						if(dummy!=0.0 || strcmp(test,single_number)!=0){
							if(memory_exp*BUFFER_SIZE <= i){
								memory_exp*=2;
								numbers=realloc(numbers,sizeof(double)*BUFFER_SIZE * memory_exp);
								if(!numbers){
									printf("Error reallocating memory for data array");
									exit(1);
								}
							}
							(*num_count)++;
							numbers[i++] = dummy;
						}
					}while(strcmp(test,single_number)!=0);
				}
			}
			fclose(fp);
			free(buffer);
			return numbers;
		} else {
			printf("Error opening \"$s\"!",source);
			exit(2);
		}
	} else {
		printf("File \"%s\" could not be found!",source);
		exit(1);
	}
}
