#ifndef CUB3D_H
# define CUB3D_H

//	headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

//	defines
#define ERROR -1
#define SUCESS 0
#define NOT_CUB "The file is not a .cub"

//	function prototypes
int	cub_verification(char *path);
void ft_error(char *message);



#endif
