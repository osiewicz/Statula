#pragma once

#define STATULA_VERSION "v0.1.15"

//flags
#define STATULA_PRINT_TO_STDOUT (1 << 0)
#define STATULA_STDIN (1 << 1)
#define STATULA_PRINT_HELP (1<<2)
#define STATULA_PRINT_FILE_NAME (1<<3)

#define STATULA_DEFAULT_PRECISION 6

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
int handle_flags(struct settings *settings);
int enable_stdin(struct settings *settings);
int is_argument(const char *argument);
int is_valid_parameter(const char *parameter, const char *long_form, const char *short_form);
struct settings *init_settings(void);
void free_settings(struct settings *settings);
void print_help(void);
struct settings *parse_cmd_args(int argc,char **argv);
