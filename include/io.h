#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char** strings(char* language);
FILE* open_lang_file(char* language);
double *read_data(const char *source,int *num_count);
