#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "statula.h"

int main(int argc,char **argv)
{
	char	*destination_file = malloc(sizeof(char)*255);
	char	*source_file = malloc(sizeof(char)*255);
	char	*language = malloc(sizeof(char)*8);
	char	file_save_check = 0;
	FILE	*save_file = NULL;
	
	source_file = "data";
	language = "en-gb";
	memset(destination_file,0,150);
  
	if(argc>1){//Check for starting parameters
		for(int i=1;i<argc;i++){
			if(strncmp(argv[i],"--",2)==0){
				if((strcmp(argv[i],"--help")==0||strcmp(argv[i],"--h")==0)&&argc-i>0){
					print_help();
					if(argc==2)
						return 0;
				} else if(strcmp(argv[i],"--o")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						source_file = argv[++i];
				} else if(strcmp(argv[i],"--l")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						language = argv[++i];
				} else if(strcmp(argv[i],"--s")==0&&argc-i>1) {
					if(strncmp(argv[i+1],"--",2)!=0)
						destination_file = argv[++i];
					file_save_check = 1;
				} else {
					printf("\nInvalid starting parameter!\n\n");
					print_help();
					return -1;
				}
			} else if(argc==2) {
				source_file = argv[1];
			} else{
				print_help();
				return -1;
			}
		}
	}
	struct dataset *set = malloc(sizeof(struct dataset));
	init_dataset(set,source_file);
	compute_dataset(set);
	
	const char **text = strings(language);
	print_dataset(set,stdout,text);

	if(file_save_check==1){
		save_file = fopen(destination_file,"w");
		if(save_file){
			print_dataset(set,save_file,text);
			fclose(save_file);
		} else {
			printf("Error opening a file for saving!");
		}
	}
	
	free_dataset(set);

	return 0;
}

void print_help(void)
{
	printf("Starting parameters:\n\
	--o * - open specified file\n\
	--s * - save result to specified file\n\
	--l pl-pl/en-gb - change interface language\n\
	--help / --h - show help page\n\n");
}
