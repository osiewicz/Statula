#include "dataset.h"
#include "io.h"
#include "statula.h"

int main(int argc,char **argv)
{
	char	**destination_file = malloc(sizeof(char*));
	char	**source_file = malloc(sizeof(char*));
	char	*language = malloc(sizeof(char)*8);
	char	file_save_check = 0;
	FILE	*save_file = NULL;
	int	file_count = 0;
	
	source_file[0] = "data";
	language = "en-gb";
  
	if(argc>1){//Check for starting parameters
		for(int i=1;i<argc;i++){
			if(strncmp(argv[i],"--",2)==0){
				if(argc-i>0 && (strcmp(argv[i],"--help")==0||strcmp(argv[i],"--h")==0)){
					print_help();
					if(argc==2)
						return 0;
				} else if(argc-i>1 && strcmp(argv[i],"--o")==0) {
					int t;
					for(t=i+1;t<argc && strncmp(argv[t],"--",2)!=0 ; t++);
					file_count += t-i-1;
					source_file = realloc(source_file,sizeof(char)*t);
					for(int j=0;j<t-i;j++){
						source_file[j] = argv[++i];
					}
				} else if(argc-i>1 && strcmp(argv[i],"--l") == 0) {
					if(strncmp(argv[i+1],"--",2)!=0)
						language = argv[++i];
				} else if(argc-i>1 && strcmp(argv[i],"--s") == 0) {
					int t;
					for(t=i+1;t<argc && strncmp(argv[t],"--",2)!=0 ; t++);
					if(file_count!=t-i-1){
						printf("%d too many/too few files specified for saving!",abs(file_count-(t - i -1)),t);
						return -1;
					} else {
						file_save_check=1;
						destination_file = realloc(destination_file,sizeof(char)*file_count);
						for(int j=0;j<t-i;j++){
							destination_file[j] = argv[++i];
						}
					}
				} else {
					printf("\nInvalid starting parameter!\n\n");
					print_help();
					return -1;
				}
			} else if(argc==2) {
				source_file[0] = argv[1];
				file_count++;
			} else{
				print_help();
				return -1;
			}
		}
	}

	const char **text = strings(language);
	struct dataset *set = malloc(sizeof(struct dataset));

	printf("\nStatula %s\n",STATULA_VERSION);
	for(int i=0;i<file_count;i++){
		init_dataset(set,source_file[i]);
		compute_dataset(set);
		print_dataset(set,stdout,text);
		if(file_save_check==1){
			save_file = fopen(destination_file[i],"w");
			if(save_file){
				print_dataset(set,save_file,text);
				fclose(save_file);
			} else {
				printf("Error creating a file named %s for saving!",destination_file[i]);
			}
		}
		free_dataset(set);
	}	
		
	free(set);
	free(destination_file);
	free(source_file);
//	free(language);

	return 0;
}

void print_help(void)
{
	printf("\nStarting parameters:\n\
	--h	Prints simple help panel.\n\
	--o 	Open specified files.\n\
	--s 	Save result to specified file.\n\
		The amount of targets must be equal to amount of files opened via --o.\n\
	--l 	Print result using specified language.\n\
		Language file has to be present in the current directory.\n\n\
	If there is just one string after \"./statula\" (not starting with \"--\"),\n\
	then it shall be used as a default filename for the session.\n\n");
}
