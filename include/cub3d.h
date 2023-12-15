#ifndef CUB3D_H
# define CUB3D_H

//	Headers ----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include "libft.h"
# include "MLX42.h"

//	Errors ----------------------------------------------------
#define ERROR -1
#define SUCESS 0

#define NOT_CUB "The file is not a .cub"
#define NO_MAP "Please pass one map as argument"

#define FD_ERROR "File does not exist or an error occured when oppening it"
#define MALLOC_ERROR "Error when allocating memory from heap"
#define READ_ERROR "Error when reading file"

#define MAP_NOT_END "Map is not at the end of the file"
#define WEIRD_CHAR "Map must contains only '0' '1' 'N' 'S' 'W' 'E' characters"  
#define MAP_OPEN "Playable map is not enclosed with walls"
#define MANY_POS "There's more than one player start position"
#define NO_POS "There is no player start position"

#define NO_TEXT "Texture does not exist"
#define BAD_COLOR "Error in the color code"

#define RANDOM "Random informations"
#define MISS_INFO "Some informations are missing"

//	Colors ----------------------------------------------------
#define RED "\033[0;31m"
#define WHITE "\033[0;0m"
 
//	Buffer size ----------------------------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define SPLIT_SEP 29

// ENUM
enum e_id
{
	NO,
	SO,
	EA,
	WE,
	C,
	F,
};  

//	Structs ----------------------------------------------------

typedef struct s_cube
{
	int 	fd;
	char	*content;
	char	*copy;
	char	*buffer;
	char	**tokens;
	char	**map;
	int		orientation;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		c_red;
	int		c_green;
	int		c_blue;
	int		f_red;
	int		f_green;
	int		f_blue;
	


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




#endif
