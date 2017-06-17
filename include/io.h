#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_COUNT 20
#define BUFFER_SIZE 1024

extern const char *progname;

const char** strings(char* language);
double *read_data(const char *source,int *num_count);
void eprintf(char *fmt,...);
