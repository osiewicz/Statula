#include "io.h"

/*** loading strings from files ***/

static FILE *open_lang_file(const char *language);

const char **load_strings(char *language)
{
	static int ref_counter = 0;
	if (ref_counter == 0)
	{
		static char *(text)[MAX_LINE_COUNT];
		char *newline_char;
		FILE *fp;
		size_t max_line_size = 100;
		fp = open_lang_file(language);
		if (!fp)
		{
			eprintf("strings: Failed to open file \".%s.lang\":", language);
		}
		for (int i = 0; i < MAX_LINE_COUNT && !feof(fp); i++)
		{
			if (getline(&(text)[i], &max_line_size, fp) > 0)
			{
				newline_char = strpbrk(text[i], "\n");
				*newline_char = 0;
			}
		}
		fclose(fp);
		ref_counter++;
		return (const char **)text;
	}
	else
	{
		eprintf("strings: Attempted reload of local strings!");
	}
}

static FILE *open_lang_file(const char *language)
{
	FILE *fp;
	char *filename = malloc(sizeof(char) * (strlen(language) + 7));
	filename[0] = '.';
	memcpy(filename + 1, language, strlen(language));
	strncat(filename + strlen(language), ".lang", 5);
	if (access(filename, F_OK) != -1)
	{
		fp = fopen(filename, "r");
		if (!fp)
		{
			eprintf("open_lang_file: Failed to open file .%s.lang:", language);
		}
	}
	else
	{
		eprintf("open_lang_file: File \".%s.lang\" was not found:", language);
	}
	return fp;
}

/*** read data from file ***/
void *read_data(const char *source, int *num_count, fpn *(*filter)(char *buffer, int *num_count, fpn *numbers))
{
	if (source == NULL || access(source, F_OK) != -1)
	{
		FILE *fp;
		char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer)
		{
			eprintf("read_data: Failed to allocate memory for line buffer:");
		}
		if (source == NULL)
			fp = stdin;
		else
			fp = fopen(source, "r");
		if (fp || source == NULL)
		{
			fpn *numbers;
			size_t size = BUFFER_SIZE;
			numbers = malloc(sizeof(fpn) * BUFFER_SIZE);

			if (!numbers)
			{
				eprintf("read_data: Failed to allocate memory for data array:");
			}
			for (int i = 0; !feof(fp);)
			{
				if (getline(&buffer, &size, fp) > 0)
				{
					numbers = filter(buffer, num_count, numbers);
				}
			}
			fclose(fp);
			free(buffer);
			return numbers;
		}
		else
		{
			eprintf("read_data: Failed to open file \"%s\":", source);
		}
	}
	else
	{
		eprintf("read_data: Failed to open file \"%s\":", source);
	}
	return NULL;
}

void eprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);
	fprintf(stderr, "%s : ", progname);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1])
		fprintf(stderr, "%s", strerror(errno));
	fprintf(stderr, "\n");
	exit(2);
}
