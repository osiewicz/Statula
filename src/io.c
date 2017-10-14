#include "io.h"

/*** loading strings from files ***/

static FILE *open_lang_file(const char *language);

char **load_strings(const char *language, int *count)
{
	/* Responsibilites:
	 * Loads strings from language file (line by line) into char array that it then returns.
	 * It stores read lines count in variable pointed to by count
	 * parameter.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	if(language == NULL || count == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_IO,"load_strings: NULL pointer passed:");
#endif
	}
	
	char **text = NULL;
	char *newline_char;
	FILE *fp;
	int i;
	size_t max_line_size = 0;
	fp = open_lang_file(language);
	if (fp == NULL) {
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_IO,"load_strings: Failed to open file \".%s.lang\":", language);
#endif
	}
	for (i = 1; feof(fp) == 0; i++) {
		char **temp = NULL;
		temp = realloc(text,sizeof(char*) * i);
		if(temp == NULL){
#ifdef STATULA_TESTS
			return NULL;
#else
			eprintf(STATULA_FAIL_MEMORY,"load_strings: Memory reallocation failed:");
#endif
		}
		text = temp;
		max_line_size=0;
		text[i-1]=NULL;
		if (getline(&(text)[i-1], &max_line_size, fp) > 0) {
			newline_char = strpbrk(text[i-1], "\n");
			if(newline_char){
				*newline_char = '\0';
			}
		}
	}
	*count = i-1;
	fclose(fp);
	 
	return text;
}

struct strings *init_strings(const char *language)
{
	/* Responsibilities:
	 * Initializes strings structure from the language name given as
	 * argument.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	if(language == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_NULL,"init_strings: NULL pointer passed:");
#endif
	}
	struct strings *strings = malloc(sizeof(struct strings));
	if(strings == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_MEMORY,"init_strings: Memory allocation failed:");
#endif
	}
	
	if(strings->text != NULL){
		free(strings->text);
	}
	
	strings->language = NULL;
	strings->line_count = 0;
	
	size_t target_len = strlen(language) + 1;
	strings->language = malloc(sizeof(char)*target_len);
	if(strings->language == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_MEMORY,"init_strings: Memcpy fail:");
#endif
	}
	
	strncpy(strings->language,language,target_len);
	strings->language[target_len - 1] = '\0';
	
	strings->text = load_strings(strings->language,&strings->line_count);
	if(strings->text == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_MEMORY,"init_strings: Loading strings fail:");
#endif
	}
	return strings;
}

int free_strings(struct strings *strings)
{
	/* Responsibilities:
	 * Frees up passed text array that should have space for MAX_LINE_COUNT elements.
	 * Memory allocation responsibilities: None.
	 */
	if(strings == NULL){
#ifdef STATULA_TESTS
		return -1;
#else
		eprintf(STATULA_FAIL_NULL,"free_strings: NULL pointer passed :");
#endif
	}
	
	for(int i=0;i<strings->line_count;i++){
		free(strings->text[i]);
	}
	free(strings->text);
	free(strings->language);
	free(strings);
	return STATULA_SUCCESS;
}

static char *get_language_dir_path(const char *language)
{
	/* Responsibilities:
	 * Returns path to .lang file based on macros defined on compile-time.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	if(language == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_NULL,"get_language_dir_path: NULL pointer passed");
#endif
	}
	size_t full_path_len = strlen(STATULA_MISC_DIR) + strlen(STATULA_LANG_DIR_NAME) + 
				strlen(language) + strlen(STATULA_LANG_FILE_EXT) + 1;
	// +1 for '\0'
	char *full_path = malloc(full_path_len * sizeof(char));
	if(full_path == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_MEMORY,"get_language_dir_path: Failed to allocate memory");
#endif
	}
	memset(full_path, 0, full_path_len);
	strcat(full_path, STATULA_MISC_DIR);
	strcat(full_path, STATULA_LANG_DIR_NAME);
	strcat(full_path, language);
	strcat(full_path, STATULA_LANG_FILE_EXT);
	
	return full_path;
}

static FILE *open_lang_file(const char *language)
{
	/* Responsibilities:
	 * Opens file for given language name (which consists of language' + ".lang").
	 * Memory allocation responsibilities: None.
	 */
	
	if(language == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_NULL,"open_lang_file: NULL pointer passed : ");
#endif
	}
	FILE *fp;
	char *filename = get_language_dir_path(language);
	if(filename == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_MEMORY,"open_lang_file: Memory allocation failed.");
#endif
	}
	if (access(filename, F_OK) != -1) {
		fp = fopen(filename, "r");
		if (fp == NULL) {
#ifdef STATULA_TESTS
			return NULL;
#else
			eprintf(STATULA_FAIL_IO,"open_lang_file: Failed to open file .%s.lang:", language);
#endif
		}
	} else {
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_IO,"open_lang_file: File \".%s.lang\" was not found:", language);
#endif
	}
	free(filename);
	return fp;
}

void *read_data(const char *source, unsigned long long *num_count, fpn *(*filter)(char *buffer, unsigned long long *num_count, fpn *numbers))
{
	/* Responsibilities:
	 * Reads data from passed 'source'. If source is NULL, it will read
	 * from stdin instead. In depth: it extracts data from file, line by
	 * line into buffer and then calls 'filter' to extract numbers from said buffer.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	if(num_count == NULL || filter == NULL){
#ifdef STATULA_TESTS
		return NULL;
#else
		eprintf(STATULA_FAIL_NULL,"read_data: NULL pointer passed : ");
#endif
	}
	if (source == NULL || access(source, F_OK) != -1){
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
			numbers = malloc(sizeof(fpn) * STATULA_BUFFER_SIZE);
			filter(NULL,NULL,NULL);//Reset memory counter in filter
	
			if (numbers == NULL) {
#ifdef STATULA_TESTS
				return NULL;
#else
				eprintf(STATULA_FAIL_MEMORY,"read_data: Failed to allocate memory for data array:");
#endif
			}
			while(feof(fp) == 0) {
				size=0;
				buffer=NULL;
				if (getline(&buffer, &size, fp) > 0) {
					numbers = filter(buffer, num_count, numbers);
				}
				free(buffer);
			}
			if(fp != stdin){
				fclose(fp);
			}
			return numbers;
		} else {
#ifdef STATULA_TESTS
			return NULL;
#else
			eprintf(STATULA_FAIL_IO,"read_data: Failed to open file \"%s\":", source);
#endif
		}
	} else {
#ifdef STATULA_TESTS
		return NULL;
#else 
		eprintf(STATULA_FAIL_IO,"read_data: Failed to access file \"%s\":", source);
#endif
	}
	return NULL;
}

unsigned eprintf(unsigned err_code, char *fmt, ...)
{
	/* Responsibilites:
	 * Prints an error in printf-like style and exits the program.
	 * Memory allocation responsibilities: None.
	 */
	
	if(fmt == NULL){
#ifdef STATULA_TESTS
		return STATULA_FAIL_NULL;
#else
		return eprintf(STATULA_FAIL_NULL,"eprintf: NULL pointer passed : ");
#endif
	}
	
	va_list args;
	fflush(stdout);
	fprintf(stderr, "%s : Error code %u", progname, err_code);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1]) {
		fprintf(stderr, "%s", strerror(errno));
	}
	fprintf(stderr, "\n");
	exit(err_code);
}

