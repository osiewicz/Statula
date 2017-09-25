#pragma once


#define STATULA_VERSION "v0.1.13"

//flags
#define PRINT_TO_STDOUT (1 << 0)
#define STDIN (1 << 1)
#define PRINT_HELP (1<<2)
#define PRINT_FILE_NAME (1<<3)

#define DEFAULT_PRECISION 6

struct strings;

struct settings{
	struct strings *strings;
	char **input_files;
	char *language;
	char **output_files;
	int dataset_flags;
	int flags;
	int in_file_count;
	int out_file_count;
	int precision;
};

int process_file(struct settings *settings,int index);
void handle_flags(struct settings *settings);
int enable_stdin(struct settings *settings);
int is_argument(char *argument);
int is_valid_parameter(char *parameter, char *long_form,char *short_form);
struct settings *init_settings(void);
void free_settings(struct settings *settings);
void print_help(void);
struct settings *parse_cmd_args(int argc,char **argv);
