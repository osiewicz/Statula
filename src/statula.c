#include "statula.h"

const char *progname;
int flags = 0;
int main(int argc, char **argv)
{
	progname = argv[0];
	char **destination_file = malloc(sizeof(char *));
	char **source_file = malloc(sizeof(char *));
	char *language = malloc(sizeof(char) * 8);
	FILE *save_file = NULL;
	int dataset_flags = 0;
	int file_count = 0;
	int t = 1;
	char **alloc_temp = NULL;
	source_file[0] = NULL;
	language = "en-gb";
	flags |= (PRINT_TO_STDOUT);
	dataset_flags |= (SORT);

	if (!destination_file || !source_file || !language)
	{
		eprintf("main: Failed to allocate memory:");
	}
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strncmp(argv[i], "--", 2) == 0)
			{
				if (argc - i > 0 && (strcmp(argv[i], "--stdin") == 0))
				{
					flags |= STDIN;
				}
				else if (argc - i > 0 && (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0))
				{
					print_help();
					if (argc == 2)
						return 0;
				}
				else if (argc - i > 0 && (strcmp(argv[i], "--nosort") == 0))
				{
					dataset_flags &= ~SORT;
				}
				else if (argc - i > 0 && (strcmp(argv[i], "--silent") == 0))
				{
					flags &= ~PRINT_TO_STDOUT;
				}
				else if (argc - i > 1 && strcmp(argv[i], "--o") == 0)
				{
					for (t = i + 1; t < argc && strncmp(argv[t], "--", 2) != 0; t++)
						;
					file_count += t - i - 1;
					alloc_temp = realloc(source_file, sizeof(char *) * file_count);
					if (!alloc_temp)
						eprintf("main: Failed to allocate memory:");
					source_file = alloc_temp;
					alloc_temp = NULL;
					for (int j = 0; j < t - i; j++)
					{
						source_file[j] = argv[++i];
					}
				}
				else if (argc - i > 1 && strcmp(argv[i], "--l") == 0)
				{
					if (strncmp(argv[i + 1], "--", 2) != 0)
						language = argv[++i];
				}
				else if (argc - i > 1 && strcmp(argv[i], "--s") == 0)
				{
					int t;
					for (t = i + 1; t < argc && strncmp(argv[t], "--", 2) != 0; t++)
						;
					if (file_count != t - i - 1)
					{
						printf("%d too many/too few files specified for saving!", abs(file_count - (t - i - 1)));
						return -1;
					}
					else
					{
						flags |= PRINT_TO_STDOUT;
						alloc_temp = realloc(destination_file, sizeof(char *) * file_count);
						if (!alloc_temp)
							eprintf("main: Failed to allocate memory:");
						destination_file = alloc_temp;
						alloc_temp = NULL;
						for (int j = 0; j < t - i; j++)
						{
							destination_file[j] = argv[++i];
						}
					}
				}
				else
				{
					printf("\nInvalid starting parameter \"%s\"!\n\n", argv[i]);
					print_help();
					return -1;
				}
			}
			else if (argc == 2)
			{
				source_file[0] = argv[1];
				file_count++;
			}
			else
			{
				print_help();
				return -1;
			}
		}
	}
	else if (argc == 1)
	{
		flags |= STDIN;
		source_file[0] = NULL;
	}

	const char **text = load_strings(language);
	struct dataset *set = malloc(sizeof(struct dataset));

	if (flags & PRINT_TO_STDOUT)
		printf("\nStatula %s\n", STATULA_VERSION);

	if (flags & STDIN)
	{
		file_count++;
		alloc_temp = realloc(source_file, sizeof(char *) * (file_count));
		if (!alloc_temp)
			eprintf("main: Failed to allocate memory");
		source_file = alloc_temp;
		alloc_temp = NULL;
		source_file[file_count - 1] = NULL;
	}

	for (int i = 0; i < file_count; i++)
	{
		init_dataset(set, dataset_flags, source_file[i]);
		compute_dataset(set);
		if (flags & PRINT_TO_STDOUT)
			print_dataset(set, stdout, text);
		if (flags & SAVE_TO_FILE)
		{
			save_file = fopen(destination_file[i], "w");
			if (save_file)
			{
				print_dataset(set, save_file, text);
				fclose(save_file);
			}
			else
			{
				eprintf("main: Failed to create file '%s':", destination_file[i]);
			}
		}
		free_dataset(set);
	}
	if ((dataset_flags ^ SORT) & SORT)
		puts("\nWARNING: Median, mode and skewness could yield incorrect results due to the input not being sorted.\n");
	free(set);
	free(destination_file);
	free(source_file);

	return 0;
}

void print_help(void)
{
	printf("\nStarting parameters:\n\
	--h		Prints simple help panel.\n\
	--o 		Open specified files.\n\
	--s 		Save result to specified file.\n\
			The amount of targets must be equal to amount of files opened via --o.\n\
	--l 		Print result using specified language.\n\
			Language file has to be present in the current directory.\n\
	--silent	Disable printing to standard output.\n\
	--nosort	Disable sorting the input.\n\
			It results in vast performance improvement at the risk of incorrect results\n\
			in mode, median and skewness. USE WITH CAUTION.\n\
	--stdin		Read directly from stdin.\n\
			It is the default behaviour if Statula does not receive any starting parameters.\n\
			Use EOF combination (which is CTRL+D on most systems) to finish data input.\n\n\
	If there is just one string after \"./statula\" (not starting with \"--\"),\n\
	then it shall be used as a default filename for the session.\n\n");
}
