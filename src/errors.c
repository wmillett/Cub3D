#include "cub3d.h"

void ft_error(char *message)
{
	gc_free_all();
	ft_putstr_fd(RED,2);
	ft_putstr_fd("Error\n",2);
	ft_putstr_fd(message,2);
	write(2,"\n",1);
	ft_putstr_fd(WHITE,2);
	exit(1);
}





