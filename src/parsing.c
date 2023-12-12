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