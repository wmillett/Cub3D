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

int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}


char	*remove_wspaces(char *line)
{
	char	**split;
	char	*copy;
	int i;
	
	i = 0;
	copy = NULL;
	split = NULL;
	while (line[i])
	{
		if (is_whitespace(line[i]) == 1)
			line[i] = SPLIT_SEP;
		i++;
	}
	split = ft_split(line, SPLIT_SEP);
	if(!split)
		return NULL;
	line = NULL;
	i = 0;
	while (split && split[i])
	{
		copy = line;
		line = ft_strjoin(copy, split[i]);
		if(!line)
			return NULL;
		free(copy);
		i++;
	}
	return (line);
}

void add_path(char *path, enum e_id id)
{
	t_cube *cube;
	
	cube = get_cube();
	if(access(path, R_OK) != 0)
		ft_error(NO_TEXT);
	if(id == NO)
	{
		if(cube->no_path)
			ft_error(EXISTS);
		cube->no_path = path;
	}
	if(id == SO)
	{
		if(cube->so_path)
			ft_error(EXISTS);
		cube->so_path = path;
	}
	if(id == EA)
	{
		if(cube->ea_path)
			ft_error(EXISTS);
		cube->ea_path = path;
	}
	if(id == WE)
	{
		if(cube->we_path) //initialize to null at first
			ft_error(EXISTS);
		cube->we_path = path;
	}
}

void add_color_code(enum e_id id, int n, int i)
{
	t_cube *cube;
	
	cube = get_cube();
	if(id == C)
	{
		if(i == 0)	
			cube->c_red = n;
		if(i == 1)	
			cube->c_green = n;
		if(i == 2)	
			cube->c_blue = n;	
	}
	if(id == F)
	{
		if(i == 0)	
			cube->f_red = n;
		if(i == 1)	
			cube->f_green = n;
		if(i == 2)	
			cube->f_blue = n;	
	}
}

void parse_color_code(char *code, enum e_id id)
{
	static int c_count = 0;
	static int f_count = 0;
	int i;
	char **split;
	int n;

	n = 0;
	split = NULL;
	i = 0;
	if(id == C)
		c_count++;
	if(id == F)
		f_count++;
	if(c_count > 1 || f_count > 1)
		ft_error(EXISTS);
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i] == ',')
		i++;
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i] == ',')
		i++;
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i])
		ft_error(BAD_COLOR);
	split = ft_split(code, ',');
	if(!split)
		ft_error(MALLOC_ERROR);
	i = 0;
	while(split[i])
	{
		n = ft_atoi(split[i]);
		if(n > 255)
			ft_error(MORE_255);
		add_color_code(id,n,i); 
		i++;
	}										
	if(i != 3)
		ft_error(BAD_COLOR);
}

void loop_line(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		while(line[i] && is_whitespace(line[i]) == true)
			i++;
		if(line[i])
		{
			if(line[i] == '1' || line[i] == '0')
			{
				get_cube()->found_map = true;
				return ;
			}
			if(line[i] == 'N' && line[i + 1] == 'O')
				return add_path(remove_wspaces(line) + 2, NO);
			if(line[i] == 'S' && line[i + 1] == 'O')
				return add_path(remove_wspaces(line) + 2, SO);
			if(line[i] == 'E' && line[i + 1] == 'A')
				return add_path(remove_wspaces(line) + 2, EA);
			if(line[i] == 'W' && line[i + 1] == 'E')
				return add_path(remove_wspaces(line) + 2, WE);
			if(line[i] == 'C')
				return parse_color_code(remove_wspaces(line) + 1, C);
			if(line[i] == 'F')
				return parse_color_code(remove_wspaces(line) + 1, F);
			else
			 	ft_error(RANDOM);
		}
		else
			return ;
		i++;
	}
}

void tokens_loop(char **tokens)
{
	t_cube *cube;
	int i;
	
	cube = get_cube();
	cube->found_map == false;
	i = 0;
	while(tokens[i])
	{
		loop_line(tokens[i]);
		if(cube->found_map == true)
			break ;
		i++;
	}
	if(!cube->no_path || !cube->so_path || !cube->ea_path 
		|| !cube->we_path || cube->c_red == -1 || cube->c_green == -1 
		|| cube->c_blue == -1 || cube->f_red == -1 || cube->f_green == -1 
		|| cube->f_blue == -1)
		ft_error(MAP_NOT_END);
	if(cube->found_map == false)
		ft_error(MAP_NOT);
	// check if weird characters in map
	// check if only one player position
	// flood fill
}

void store_file(t_cube*cube)
{
	read_file(cube);
	
	cube->tokens = ft_split(cube->content,'\n');
	if(!cube->tokens)
		ft_error(MALLOC_ERROR);
	//print_tab(cube->tokens);
	//printf("here: %s\n", cube->tokens[5]);
	tokens_loop(cube->tokens);
	
	//printf("here %d\n",get_cube()->c_blue);
	//cube->content = ft_free(cube->content);
	//printf("%s\n", remove_wspaces(cube->tokens[0],0));
	//add_path(remove_wspaces(cube->tokens[0],0));

	

}

// NO . / pa th     a 1       valid it seems.      5  15  is 515
// if more than one same texture/color    not valid
// 1 or 0 in separate line is begining of map
// others than 1 and 0 in seprate line    not valid
//check if first 0-1 in separate line is found after all infos are found. after check if other chars in the map





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

//use acess to test if path is good

//finalement: le NWES peut etre dans nimporte quel ordre, new line defini la fin. les couleurs vont apres, nimporte quel ordre, new line 
//definie la fin
// la map est a la fin
//peut avoir whitespaces

// finalement les spaces egalent pas 0