#pragma once

#define STATULA_VERSION "v0.1.10"

//flags
#define PRINT_TO_STDOUT (1 << 0)
#define SAVE_TO_FILE (1 << 1)
#define STDIN (1 << 2)

#define DEFAULT_PRECISION 6

#include "dataset.h"
#include "io.h"

extern const char *progname;

void print_help(void);
