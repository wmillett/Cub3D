#include "cub3d.h"

void ft_error(char *message)
{
	ft_free_all(get_cube());
	ft_putstr_fd(RED,2);
	ft_putstr_fd("Error\n",2);
	ft_putstr_fd(message,2);
	write(2,"\n",1);
	ft_putstr_fd(WHITE,2);
	exit(1);
}

void free_table(char **table)
{
	int i;

	i = 0;
	while(table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void ft_free_all(t_cube	*cube)
{
	if(cube->fd < 0)
		close(cube->fd);
	if(cube->buffer)
		free(cube->buffer);
	if(cube->copy)
		free(cube->copy);
	if(cube->content)
		free(cube->content);
	if(cube->tokens)
		free_table(cube->tokens);
	if(cube->map)
		free_table(cube->map);
}

void *ft_free(void*adress)
{
	free(adress);
	return NULL;
}
