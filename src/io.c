#include "io.h"

/*** loading strings from files ***/

static FILE* open_lang_file(const char* language);

const char **strings(char *language)
{
	static char *(text)[MAX_LINE_COUNT];
	char *newline_char;
	FILE *fp;
	size_t max_line_size=100;
	fp=open_lang_file(language);
	if(!fp){
		eprintf("strings: Failed to open file \".%s.lang\":",language);
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

static FILE* open_lang_file(const char* language)
{
	FILE* fp;
	char *filename = malloc(sizeof(char)*(strlen(language)+7));
	filename[0]='.';
	memcpy(filename+1,language,strlen(language));
	strncat(filename+strlen(language),".lang",5);
	if( access( filename, F_OK ) != -1 ) {
		fp=fopen(filename,"r");
		if(!fp){
			eprintf("open_lang_file: Failed to open file .%s.lang:",language);
		}
	} else {
		eprintf("open_lang_file: File \".%s.lang\" was not found:",language);
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
			eprintf("read_data: Failed to allocate memory for line buffer:");
		}
		fp=fopen(source,"r");
		if(fp){
			char	*single_number = NULL;
			char	*test = NULL;
			double	dummy;
			double	*temporary_pointer = NULL;
			double	*numbers;
			int	memory_exp = 1;
			size_t	size = BUFFER_SIZE;
			numbers=malloc(sizeof(double)*BUFFER_SIZE*memory_exp);


			if(!numbers){
				eprintf("read_data: Failed to allocate memory for data array:");
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
								temporary_pointer=realloc(numbers,sizeof(double)*BUFFER_SIZE * memory_exp);
								if(!temporary_pointer){
									eprintf("read_data: Failed to reallocate memory for data array:");
								}
								numbers=temporary_pointer;
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
			eprintf("read_data: Failed to open file \"$s\":",source);
		}
	} else {
		eprintf("read_data: Failed to open file \"$s\":",source);
	}
	return NULL;
}

void eprintf(char *fmt, ...)
{
	va_list args;
	
	fflush(stdout);
	fprintf(stderr,"%s : ",progname);
	va_start(args, fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	
	if(fmt[0] != '\0' &&fmt[strlen(fmt)-1])
		fprintf(stderr, "%s",strerror(errno));
	fprintf(stderr,"\n");
	exit(2);
}
