#include "cub3d.h"

int main(int argc, char **argv)
{    
	// char *file_name;

	// file_name = argv[1] + 5;
	if(argc < 2)
		return 1; 
	//printf("%s\n",file_name);
	if(cub_verification(argv[1]) == 0)
		printf("approved\n");
	else
		ft_error(NOT_CUB);
	return 0;
}