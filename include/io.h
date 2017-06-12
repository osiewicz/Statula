#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_COUNT 20
#define BUFFER_SIZE 1024

const char** strings(char* language);
FILE* open_lang_file(const char* language);
double *read_data(const char *source,int *num_count);
