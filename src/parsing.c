#include "cub3d.h"

int	cub_verification(char *path)
{
	int	len;
         
	len = ft_strlen(path);
	if (len > 4 && path[len - 5] != '/' && ft_tolower(path[len - 1]) == 'b' && 
		ft_tolower(path[len- 2]) == 'u' && ft_tolower(path[len - 3]) == 'c' && path[len - 4] == '.')
		return (SUCESS);
	return (ERROR);
} 

void read_file(t_cube*cube)
{
	int read_return;

	read_return = 0;
	//cube->copy = NULL;
	//cube->buffer = NULL;
	cube->buffer = ft_calloc(sizeof(char),BUFFER_SIZE + 1);
	if(!cube->buffer)
		ft_error(MALLOC_ERROR);
	while(1) 
	{
		read_return = read(cube->fd, cube->buffer, BUFFER_SIZE);
		if(read_return == ERROR)
			ft_error(READ_ERROR);
		if(read_return == 0)
			break;
		cube->copy = cube->content;
		cube->content  = ft_strjoin(cube->copy, cube->buffer);
		if(!cube->content)
			ft_error(MALLOC_ERROR);
		cube->copy = ft_free(cube->copy);
		ft_bzero(cube->buffer,BUFFER_SIZE+1);
	}
	cube->buffer = ft_free(cube->buffer);
}

void store_file(t_cube*cube)
{
	read_file(cube);
	cube->split = ft_split(cube->content,'\n');
	if(!cube->split)
		ft_error(MALLOC_ERROR);
	cube->content = ft_free(cube->content);
	print_tab(cube->split);
	

}
//dont forget to close fd when error

//store all the file in a char**
//extract infos
//store the map in a char**
//free the file char**


//partie jouable du joueur doit etre entourer de murs, autour on sen fou si cest ouvert
//un N,W,E,S
// zero or many D(doors) for bonus

//instructions peuvent avoir whitespaces around them mais juste ca
//quand ont trouve soit un 0,1,n,s,e,o la map commence
//map peut avoir des spaces qui egale des 0. pour la map, tout les strings = len de la plus longue
// fill avec des spaces le gap apres les strings pour la minimap
//separer bonus de partie mendatoire