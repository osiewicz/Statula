#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dataset.h>

#define STATULA_BUFFER_SIZE 1024

extern const char *progname;

struct strings{
	char **text;
	char *language;
	int line_count;
};

char **load_strings(const char *language,int *count);
struct strings *init_strings(const char *language);
int free_strings(struct strings *strings);
void *read_data(const char *source, int *num_count, fpn *(*filter)(char *buffer, int *num_count, fpn *numbers));
void eprintf(char *fmt, ...);
