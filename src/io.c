#include "io.h"

/*** loading strings from files ***/

static FILE *open_lang_file(const char *language);

char **load_strings(char *language)
{
	/* Responsibilites:
	 * Loads strings (line by line) into structure that it then returns.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	char **text = malloc(sizeof(char*) * MAX_LINE_COUNT);
	char *newline_char;
	FILE *fp;
	size_t max_line_size = 0;
	fp = open_lang_file(language);
	if (!fp) {
		eprintf("strings: Failed to open file \".%s.lang\":", language);
	}
	for (int i = 0; i < MAX_LINE_COUNT && !feof(fp); i++) {
		max_line_size=0;
		text[i]=NULL;
		if (getline(&(text)[i], &max_line_size, fp) > 0) {
			newline_char = strpbrk(text[i], "\n");
			*newline_char = '\0';
		}
	}
	fclose(fp);
	 
	return text;
}

void free_strings(char **text)
{
	/* Responsibilities:
	 * Frees up passed text array that should have space for MAX_LINE_COUNT elements.
	 * Memory allocation responsibilities: None.
	 */
	
	for(int i=0;i<MAX_LINE_COUNT&&text[i]!=NULL;i++){
		free(text[i]);
	}
	free(text);
}

static FILE *open_lang_file(const char *language)
{
	/* Responsibilities:
	 * Opens file for given language name (which consists of "."
	 * + 'language' + ".lang").
	 * Memory allocation responsibilities: None.
	 */
	
	FILE *fp;
	char *filename = malloc(sizeof(char) * (strlen(language) + 7*sizeof(char)));
	memset(filename,0,sizeof(char)*strlen(language)+7*sizeof(char));
	filename[0] = '.';
	memcpy(filename + 1, language, strlen(language));
	strncat(filename + strlen(language), ".lang", 5);
	if (access(filename, F_OK) != -1) {
		fp = fopen(filename, "r");
		if (!fp) {
			eprintf("open_lang_file: Failed to open file .%s.lang:", language);
		}
	} else {
		eprintf("open_lang_file: File \".%s.lang\" was not found:", language);
	}
	free(filename);
	return fp;
}

void *read_data(const char *source, int *num_count, fpn *(*filter)(char *buffer, int *num_count, fpn *numbers))
{
	/* Responsibilities:
	 * Reads data from passed 'source'. If source is NULL, it will read
	 * from stdin instead. In depth: it extracts data from file, line by
	 * line into buffer and then calls 'filter' to extract numbers from said buffer.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	if (source == NULL || access(source, F_OK) != -1)
	{
		FILE *fp;
		char *buffer = NULL;
		if (source == NULL) {
			fp = stdin;
		} else {
			fp = fopen(source, "r");
		}
		if (fp  || source == NULL) {
			fpn *numbers;
			size_t size = 0;
			numbers = malloc(sizeof(fpn) * BUFFER_SIZE);
			filter(NULL,NULL,NULL);//Reset memory counter in filter
	
			if (!numbers) {
				eprintf("read_data: Failed to allocate memory for data array:");
			}
			while(!feof(fp)) {
				size=0;
				buffer=NULL;
				if (getline(&buffer, &size, fp) > 0) {
					numbers = filter(buffer, num_count, numbers);
				}
				free(buffer);
			}
			if(fp!=stdin){
				fclose(fp);
			}
			return numbers;
		} else {
			eprintf("read_data: Failed to open file \"%s\":", source);
		}
	} else {
		eprintf("read_data: Failed to access file \"%s\":", source);
	}
	return NULL;
}

void eprintf(char *fmt, ...)
{
	/* Responsibilites:
	 * Prints an error in printf-like style and exits the program.
	 * Memory allocation responsibilities: None.
	 */
	
	va_list args;
	fflush(stdout);
	fprintf(stderr, "%s : ", progname);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1]) {
		fprintf(stderr, "%s", strerror(errno));
	}
	fprintf(stderr, "\n");
	exit(2);
}

