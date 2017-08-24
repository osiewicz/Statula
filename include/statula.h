#pragma once


#define STATULA_VERSION "v0.1.11"

//flags
#define PRINT_TO_STDOUT (1 << 0)
#define SAVE_TO_FILE (1 << 1)
#define STDIN (1 << 2)
#define PRINT_HELP (1<<3)
#define PRINT_FILE_NAME (1<<4)

#define DEFAULT_PRECISION 6
struct settings{
	const char **text;
	char **input_files;
	char *language;
	char **output_files;
	int dataset_flags;
	int flags;
	int in_file_count;
	int out_file_count;
	int precision;
};



#include "dataset.h"
#include "io.h"

extern const char *progname;

void print_help(void);
struct settings *parse_cmd_args(int argc,char **argv);
