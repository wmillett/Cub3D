#ifndef CUB3D_H
# define CUB3D_H

//	Headers ----------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "MLX42.h"
// For Raycasting
# include <math.h>

//	Errors ----------------------------------------------------
# define ERROR -1
# define SUCESS 0
# define NOT_CUB "The file is not a .cub"
# define NO_MAP "Please pass one map as argument"
# define FD_ERROR "File does not exist or an error occured when oppening it"
# define MALLOC_ERROR "Error when allocating memory from heap"
# define READ_ERROR "Error when reading file"

//	Colors ----------------------------------------------------
# define RED "\033[0;31m"
# define WHITE "\033[0;0m"
 
//	Buffer size ----------------------------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// ENUM
enum e_orien
{
	N,
	S,
	E,
	w,
};  

//	Structs ----------------------------------------------------

typedef struct s_raycast
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
}	t_raycast;

typedef struct s_cube
{
	int 	fd;
	char	*content;
	char	*copy;
	char	*buffer;
	char	**split;
	char	**map;
	int		orientation;
	t_raycast *coordinates;
}	t_cube;

t_cube	*get_cube();

//	Parsing ----------------------------------------------------
int	cub_verification(char *path);
void read_file(t_cube*cube);
void store_file(t_cube*cube);

//	Errors and free ----------------------------------------------------
void ft_error(char *message);
void ft_free_all(t_cube	*cube);
void free_table(char **table);
void *ft_free(void*adress);
// Testing ------------------------------------------------
void print_tab(char**split);
// Raycasting ------------------------------------------------




#endif
