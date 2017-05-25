#include "io.h"

/*** loading strings from files ***/

const char **strings(char *language)
{
	static char *(text)[20];
	char *newline_char;
	FILE *fp;
	size_t t=100;
	fp=open_lang_file(language);
	if(!fp){
		printf("Could not open file .%s.lang.\n",language);
		exit(0);
	}
	for(int i=0;!feof(fp);i++){
		if(getline(&(text)[i],&t,fp)>0){
			newline_char=strpbrk(text[i],"\n");
			*newline_char=0;
			continue;
		}
	}
	fclose(fp);
	return (const char**)text;
}

FILE* open_lang_file(char* language)
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
		exit(0);
	}
	return fp;
}

/*** read data from file ***/

double *read_data(const char* source,int* num_count)
{
	if( access( source, F_OK ) != -1 ) {
		FILE *fp;
		char *buffer = malloc(sizeof(char)*4096);
		fp=fopen(source,"r");
		double dummy;
		size_t size = 8192;
		char *single_number = NULL;
		char *test = NULL;
		for(int i=0;!feof(fp);i++){
			if(getline(&buffer,&size,fp)>0){
				single_number = buffer; 
				do{
					test = single_number;
					dummy = strtod(single_number,&single_number);
					if(dummy!=0.0 || strcmp(test,single_number)!=0)
						(*num_count)++;
				}while(strcmp(test,single_number)!=0);
			}
		}
		double *numbers=malloc(sizeof(double)*(*num_count));
		rewind(fp);
		for(int i=0;i<(*num_count) && !feof(fp);){
			if(getline(&buffer,&size,fp)>0){
				single_number = buffer;
				do{
					test = single_number;
					dummy = strtod(single_number,&single_number);
					if(dummy != 0.0 || strcmp(test,single_number)!=0)
					numbers[i++] = dummy;
				}while(strcmp(test,single_number)!=0);
			}
		}
		fclose(fp);
		free(buffer);
		return numbers;
	} else {
		printf("File \"%s\" could not be found!",source);
		exit(1);
	}
}
