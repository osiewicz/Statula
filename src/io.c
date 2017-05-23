#include "io.h"

/*** loading strings from files ***/

const char **strings(char *language)
{
	static char *(text)[20];
	char *newline_char;
	FILE *fp;
	size_t t=100;
	fp=open_lang_file(language);

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
	if(strcmp(language,"en-gb")==0){
		if( access( ".en-gb.lang", F_OK ) != -1 ) {
			fp=fopen(".en-gb.lang","r");
		} else {
			printf("Language pack for %s is missing!"
			" Consider using other language packs or download them from"
			" GitHub repository.",language);
			exit(0);
		}
	} else if(strcmp(language,"pl-pl")==0){
		if( access( ".pl-pl.lang", F_OK ) != -1 ) {
			fp=fopen(".pl-pl.lang","r");
		} else {
			printf("Language pack for %s is missing!"
			" Consider using other language packs or download them from"
			" GitHub repository.",language);
			exit(0);
		}
	} else{
		printf("Your package is corrupted! Please consider redownloading"
		" whole package at https://github.com/PiotrOsiewicz/Statula\n");
		exit(0);
	}
	return fp;
}

/*** read data from file ***/

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
