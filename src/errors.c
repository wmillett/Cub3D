#include "cub3d.h"

void ft_error(char *message)
{
	ft_putstr_fd(message,2);
	write(2,"\n",1);
	//free here
	exit(1);
}