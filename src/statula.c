#include "statula.h"
#include "dataset.h"
#include "io.h"

const char *progname;

int main(int argc, char **argv)
{
	/* Responsibilites:
	 * Main driver function - gets the list of input files from command
	 * line parser and then calls appropiate functions for each one of them.
	 * Memory allocation responsibilities: Delegated to other functions.
	 */
	
	progname = argv[0];
	
	/*progname is used by eprintf - unfortunately it could
	 * either be passed to every function in case it wanted to call eprintf or I 
	 * could have made it a global. I went with the latter approach.
	 */
	
	struct settings *settings = parse_cmd_args(argc,argv); 
	
	handle_flags(settings);
	for (int i = 0; i < settings->in_file_count; i++) {
		process_file(settings,i);
	}
	
	if ((settings->dataset_flags ^ SORT) & SORT) {
		puts("\nWARNING: Median, mode and skewness could yield incorrect results due to the input not being sorted.\n");
	}
	
	free_settings(settings);
	
	return 0;
}
void process_file(struct settings *settings, int index)
{
	/* Responsibilities:
	 * Calls appropiate functions to load, calculate, display and save
	 * results to file from filename at settings->input_files[index].
	 * Allocated memory is freed up before returning.
	 * Memory allocation responsibilities: None.
	 */

	if(index >= settings->in_file_count || index<0){
		return;
	}
	struct dataset *set = malloc(sizeof(struct dataset));
	if(set == NULL){
		eprintf("process_file: Failed to allocate memory for set.");
	}
	init_dataset(set, settings->dataset_flags, settings->input_files[index]);
	compute_dataset(set);
	if (settings->flags & PRINT_TO_STDOUT) {
		print_dataset(set, stdout, settings,settings->input_files[index]);
	}
	if (index<settings->out_file_count) {
		FILE *save_file = fopen(settings->output_files[index], "w");
		if (save_file) {
			print_dataset(set, save_file, settings,settings->input_files[index]);
			fclose(save_file);
		} else {
			eprintf("process_file: Failed to create file '%s':", settings->output_files[index]);
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
	
	if (settings->flags & PRINT_TO_STDOUT) {
		printf("\nStatula %s\n", STATULA_VERSION);
	}
	if((settings->flags & PRINT_HELP) != 0){
		print_help();
	}
	if (settings->flags & STDIN) {
		enable_stdin(settings);
	}
}

void enable_stdin(struct settings *settings)
{
	/* Responsibilities:
	 * Adding NULL, dummy file name which is later on interpreted as stdin
	 * to the list of files.
	 * Memory allocation responsibilities: Allocates memory.
	 */
	
	char** alloc_temp;
	alloc_temp = realloc(settings->input_files, sizeof(char *) * (settings->in_file_count+1));
	if (!alloc_temp) {
		eprintf("main: Failed to allocate memory");
	}
	settings->in_file_count++;
	settings->input_files = alloc_temp;
	alloc_temp = NULL;
	settings->input_files[settings->in_file_count - 1] = NULL;
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
	result->input_files = NULL;
	result->output_files = NULL;
	result->language = "en-gb";
	result->dataset_flags = 0;
	result->flags = 0;
	result->in_file_count = 0;
	result->out_file_count = 0;
	result->precision = DEFAULT_PRECISION;
	result->flags |= (PRINT_TO_STDOUT);
	result->dataset_flags |= (SORT);
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
	free_strings(settings->text);
	free(settings);
}

struct settings *parse_cmd_args(int argc,char **argv)
{
	/* Responsibilities:
	 * Goes through argv and puts it's contents into settings struct that it will return later. 
	 * Memory allocation responsibilities: Delegated to other functions.
	 */
	
	struct settings *settings = init_settings();
	int t = 1;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (strncmp(argv[i], "-", 1) == 0) {
				if(argc - i > 0 && is_valid_parameter(argv[i],"--print_name",NULL) == 1){
					settings->flags |= PRINT_FILE_NAME;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--stdin",NULL) == 1)) {
					settings->flags |= STDIN;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--help","-h") == 1)) {
					settings->flags |= PRINT_HELP;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--nosort",NULL) == 1)) {
					settings->dataset_flags &= ~SORT;
				} else if (argc - i > 0 && (is_valid_parameter(argv[i], "--silent",NULL) == 1)) {
					settings->flags &= ~PRINT_TO_STDOUT;
				} else if (argc - i > 1 && is_valid_parameter(argv[i],"--precision",NULL) == 1){
					settings->precision = strtol(argv[i+1],NULL,10);
					if(settings->precision<0){
						settings->precision = DEFAULT_PRECISION;
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
					print_help();
					eprintf("\nInvalid starting parameter \"%s\"!\n\n", argv[i]);
				}
			} else if (argc == 2 && is_argument(argv[1])==1) {
				settings->input_files = malloc(sizeof(char *));
				settings->input_files[0] = argv[1];
				settings->in_file_count++;
			} else {
				print_help();
				eprintf("\nInvalid starting parameter \"%s\"!\n\n", argv[i]);
			}
		}
	} else if (argc == 1) {
		settings->flags |= STDIN;
	}
	settings->text = load_strings(settings->language);
	return settings;
}

