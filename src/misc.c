#include <dataset.h>
#include <io.h>

int process_file(struct settings *settings, int index)
{
	/* Responsibilities:
	 * Calls appropiate functions to load, calculate, display and save
	 * results to file from filename at settings->input_files[index].
	 * Allocated memory is freed up before returning.
	 * Memory allocation responsibilities: None.
	 */
	if(settings == NULL){
#ifdef TEST
		return -1;
#else
		eprintf("process_file: NULL pointer passed:");
#endif
	}
	if(index >= settings->in_file_count || index<0){
#ifdef TEST
		return -2;
#else
		eprintf("process_file: Invalid parameters:");
#endif
	}
	struct dataset *set = malloc(sizeof(struct dataset));
	if(set == NULL){
#ifdef TEST
		return -3;
#else
		eprintf("process_file: Failed to allocate memory for set.");
#endif
	}
	init_dataset(set, settings->dataset_flags, settings->input_files[index]);
	compute_dataset(set);
	if (settings->flags & STATULA_PRINT_TO_STDOUT) {
		print_dataset(set, stdout, settings,settings->input_files[index]);
	}
	if (index<settings->out_file_count) {
		FILE *save_file = fopen(settings->output_files[index], "w");
		if (save_file) {
			print_dataset(set, save_file, settings,settings->input_files[index]);
			fclose(save_file);
		} else {
#ifdef TEST
			return -4;
#else
			eprintf("process_file: Failed to create file '%s':", settings->output_files[index]);
#endif
		}
	}
	free_dataset(set);
}

void handle_flags(struct settings *settings)
{
	/* Responsibilities: 
	 * Calling appropiate functions if given flag is (not) set.
	 * Memory allocation responsibilities: None.
	 */
	
	if (settings->flags & STATULA_PRINT_TO_STDOUT) {
		printf("\nStatula %s\n", STATULA_VERSION);
	}
	if((settings->flags & STATULA_PRINT_HELP) != 0){
		print_help();
	}
	if (settings->flags & STATULA_STDIN) {
		enable_stdin(settings);
	}
}

int enable_stdin(struct settings *settings)
{
	/* Responsibilities:
	 * Adding NULL, dummy file name which is later on interpreted as stdin
	 * to the list of files.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	if(settings == NULL){
#ifdef TEST
		return -1;
#else
		eprintf("enable_stdin: NULL pointer passed:");
#endif
	}
	char** alloc_temp;
	alloc_temp = realloc(settings->input_files, sizeof(char *) * (settings->in_file_count+1));
	if (!alloc_temp) {
#ifdef TEST
		return -2;
#else
		eprintf("enable_stdin: Failed to allocate memory");
#endif
	}
	settings->in_file_count++;
	settings->input_files = alloc_temp;
	alloc_temp = NULL;
	settings->input_files[settings->in_file_count - 1] = NULL;
	return 0;
}

void print_help(void)
{
	/* Responsibilities:
	 * Prints help panel.
	 * Memory allocation responsibilities: None.
	 */
	
	printf("\nStarting parameters:\n\
	-h/--help	Prints simple help panel.\n\
	-o/--open 	Open specified files.\n\
	-s/--save 	Save result to specified file.\n\
			The amount of targets must be equal to amount of files opened via --o.\n\
	-l/--language	Print result using specified language.\n\
			Language file has to be present in the current directory.\n\
	--silent	Disable printing to standard output.\n\
	--nosort	Disable sorting the input.\n\
			It results in vast performance improvement at the risk of incorrect results\n\
			in mode, median and skewness. USE WITH CAUTION.\n\
	--stdin		Read directly from stdin.\n\
			It is the default behaviour if Statula does not receive any starting parameters.\n\
			Use EOF combination (which is CTRL+D on most systems) to finish data input.\n\
	--print_name	Print file name above each dataset.\n\n\
	If there is just one string after \"./statula\" (not starting with \"--\"),\n\
	then it shall be used as a default filename for the session.\n\n");
}

int is_argument(char *argument)
{
	/* Responsibilities:
	 * Checks whether argument meets argument criteria - not being NULL and
	 * not starting with '-'.
	 * Memory allocation responsibilities: None.
	 */
	
	return argument == NULL || strncmp(argument,"-",1) == 0 ?0:1;
}

int is_valid_parameter(char *parameter,char *long_form, char *short_form)
{
	/* Responsibilities:
	 * Compares long_form and short_form with parameter and returns 1
	 * if either one of them is equal to parameter.
	 * Memory allocation responsibilities: None.
	 */
	
	int short_result = 1;
	int long_result = 1;
	if(long_form!=NULL){
		long_result = strcmp(parameter,long_form);
	}
	if(short_form != NULL){
		short_result = strcmp(parameter,short_form);
	}
	return (long_result == 0 || short_result == 0)?1:0;
}

struct settings *init_settings(void)
{
	/* Responsibilities:
	 * Sets settings struct to default values.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	struct settings *result = malloc(sizeof(struct settings));

	if(!result){
		return NULL;
	}
	result->input_files = NULL;
	result->output_files = NULL;
	result->language = "en-gb";
	result->dataset_flags = 0;
	result->flags = 0;
	result->in_file_count = 0;
	result->out_file_count = 0;
	result->precision = STATULA_DEFAULT_PRECISION;
	result->flags |= (STATULA_PRINT_TO_STDOUT);
	result->dataset_flags |= (STATULA_SORT);
	return result;
}

void free_settings(struct settings *settings)
{
	/* Responsibilities:
	 * Cleans up settings structure.
	 * Memory allocation responsibilities: None.
	 */
	
	free(settings->output_files);
	free(settings->input_files);
	free_strings(settings->strings);
	free(settings);
}

struct settings *parse_cmd_args(int argc,char **argv)
{
	/* Responsibilities:
	 * Goes through argv and puts it's contents into settings struct that it will return later. 
	 * Memory allocation responsibilities: Delegated to other functions.
	 */
	
	if(argv == NULL || argc <= 0)
	{
#ifdef TEST
		return NULL;
#else
		eprintf("parse_cmd_args: NULL pointer passed:");
#endif
	}
	
	struct settings *settings = init_settings();
	if(!settings){
#ifdef TEST
		return NULL;
#else
		eprintf("parse_cmd_args: Memory allocation fail:");
#endif
	}
	int t = 1;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (strncmp(argv[i], "-", 1) == 0) {
				if(argc - i > 0 && is_valid_parameter(argv[i],"--print_name",NULL) == 1){
					settings->flags |= STATULA_PRINT_FILE_NAME;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--stdin",NULL) == 1)) {
					settings->flags |= STATULA_STDIN;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--help","-h") == 1)) {
					settings->flags |= STATULA_PRINT_HELP;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--nosort",NULL) == 1)) {
					settings->dataset_flags &= ~STATULA_SORT;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--silent",NULL) == 1)) {
					settings->flags &= ~STATULA_PRINT_TO_STDOUT;
				} else if (argc - i > 1 && is_valid_parameter(argv[i],"--precision",NULL) == 1){
					settings->precision = strtol(argv[i+1],NULL,10);
					if(settings->precision<0){
						settings->precision = STATULA_DEFAULT_PRECISION;
					}
					i++;
				} else if (argc - i > 1 && (is_valid_parameter(argv[i], "--open","-o")==1)) {
					for (t = i + 1; t < argc && is_argument(argv[t]) == 1; t++)
						{ }
					if(settings->in_file_count==0){
						settings->in_file_count = t - i - 1;
					}
					if(settings->input_files == NULL){
						settings->input_files = malloc( sizeof(char *) * settings->in_file_count);
						for (int j = 0; j < settings->in_file_count; j++) {
							settings->input_files[j] = argv[++i];
						}
					}
				} else if (argc - i > 1 && (is_valid_parameter(argv[i], "--language","-l") == 1)) {
					if (is_argument(argv[i+1])==1) {
						settings->language = argv[++i];
					}
				} else if (argc - i > 1 && is_valid_parameter(argv[i],"--save","-s")==1) {
					int t;
					for (t = i + 1; t < argc && is_argument(argv[t]) == 1; t++)
						{ }
					if(settings->out_file_count==0){
						settings->out_file_count = t-i-1;
					}
					if(settings->output_files == NULL){
						settings->output_files = malloc(sizeof(char*)*settings->out_file_count);
						for (int j = 0; j < settings->out_file_count ; j++) {
							settings->output_files[j] = argv[++i];
						}
					}
				} else {
#ifdef TEST
					return NULL;
#else
					print_help();
					eprintf("\nInvalid starting parameter \"%s\"!\n\n", argv[i]);
#endif
				}
			} else if (argc == 2 && is_argument(argv[1])==1) {
				settings->input_files = malloc(sizeof(char *));
				settings->input_files[0] = argv[1];
				settings->in_file_count++;
			} else {
#ifdef TEST
				return NULL;
#else
				print_help();
				eprintf("\nInvalid starting parameter \"%s\"!\n\n", argv[i]);
#endif
			}
		}
	} else if (argc == 1) {
		settings->flags |= STATULA_STDIN;
	}
	
	settings->strings = init_strings(settings->language);
	
	if(!settings->strings){
#ifdef TEST
		return NULL;
#else
		eprintf("parse_cmd_args: Init strings fail:");
#endif
	}
	
	return settings;
}

