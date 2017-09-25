#include <misc.h>
#include <dataset.h>
#include <io.h>

const char *progname;

int main(int argc, char **argv)
{
	/* Responsibilites:
	 * Main driver function - gets the list of input files from command
	 * line parser and then calls appropiate functions for each one of them.
	 * Memory allocation responsibilities: Delegated to other functions.
	 */
	
	progname = argv[0];
	
	/*progname is used by eprintf - unfortunately it could
	 * either be passed to every function in case it wanted to call eprintf or I 
	 * could have made it a global. I went with the latter approach.
	 */
	
	struct settings *settings = parse_cmd_args(argc,argv); 
	
	handle_flags(settings);
	for (int i = 0; i < settings->in_file_count; i++) {
		process_file(settings,i);
	}
	
	if ((settings->dataset_flags ^ SORT) & SORT) {
		puts("\nWARNING: Median, mode and skewness could yield incorrect results due to the input not being sorted.\n");
	}
	
	free_settings(settings);
	
	return 0;
}

