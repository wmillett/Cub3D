#ifndef CUB3D_H
# define CUB3D_H

//	Headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
# include "MLX42.h"

//	Errors
#define ERROR -1
#define SUCESS 0
#define NOT_CUB "The file is not a .cub"
#define NO_MAP "Please pass one map as argument"

// Colors
#define RED "\033[0;31m"
#define WHITE "\033[0;0m"

//	Structs
typedef struct s_cube
{

}	t_cube;

//	Function prototypes

t_cube	*get_cube();

int	cub_verification(char *path);
void ft_error(char *message);



#endif
