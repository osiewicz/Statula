#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dataset.h>

#define MAX_LINE_COUNT 20
#define BUFFER_SIZE 1024

extern const char *progname;

char **load_strings(char *language);
void free_strings(char **text);
void *read_data(const char *source, int *num_count, fpn *(*filter)(char *buffer, int *num_count, fpn *numbers));
void eprintf(char *fmt, ...);
