#include "cub3d.h"

t_cube	*get_cube()
{
	static t_cube cube;

	return (&cube);
}

void set_cube_struct(t_cube* cube)
{

	cube->fd = -1;
	cube->buffer = NULL;
	cube->copy = NULL;
	cube->content = NULL;
	cube->tokens = NULL;
	cube->map = NULL;	
}

void print_tab(char**split)
{
	int i = 0;
	if(!split)
		return ;
	while(split[i])
	{
		printf("%s\n",split[i]);
		i++;
	}
}


int main(int argc, char **argv)
{
	set_cube_struct(get_cube()); 
	if(argc < 2)
		ft_error(NO_MAP);
	if(cub_verification(argv[1]) == ERROR)
		ft_error(NOT_CUB);     
	get_cube()->fd = open(argv[1], O_RDONLY);
	if(get_cube()->fd == ERROR)
		ft_error(FD_ERROR);
	
	store_file(get_cube());
	

	

	// ft_window(get_cube());
	
	ft_free_all(get_cube());
	return SUCESS; 
}