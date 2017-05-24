#pragma once

#include "basic_operations.h"
#include "medium_operations.h"
#include "io.h"

int init_dataset(struct dataset *set,const char *source);
int free_dataset(struct dataset *set);
int compute_dataset(struct dataset *set);
int print_dataset(struct dataset *set,FILE* stream,const char **text);
