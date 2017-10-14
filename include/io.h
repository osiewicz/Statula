#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dataset.h>

#define STATULA_BUFFER_SIZE 1024
#define STATULA_LANG_FILE_EXT ".lang"

#ifndef STATULA_MISC_DIR
#define STATULA_MISC_DIR "./"
#endif

#ifndef STATULA_LANG_DIR_NAME
#define STATULA_LANG_DIR_NAME "lang/"
#endif

#define STATULA_SUCCESS 0
#define STATULA_FAIL_NULL 1
#define STATULA_FAIL_MEMORY 2
#define STATULA_FAIL_IO 3
#define STATULA_FAIL_GENERAL 4
#define STATULA_FAIL_MATH 5

extern const char *progname;

struct strings{
	char **text;
	char *language;
	int line_count;
};

char **load_strings(const char *language,int *count);
struct strings *init_strings(const char *language);
int free_strings(struct strings *strings);
void *read_data(const char *source, unsigned long long *num_count, fpn *(*filter)(char *buffer, unsigned long long *num_count, fpn *numbers));
unsigned eprintf(unsigned err_code, char *fmt, ...);
