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
	if(access(path, R_OK) != 0)
		ft_error(NO_TEXT);
	if(id == NO)
		get_cube()->no_path = path;
	if(id == SO)
		get_cube()->so_path = path;
	if(id == EA)
		get_cube()->ea_path = path;
	if(id == WE)
		get_cube()->we_path = path;
}

void add_color_code(enum e_id id, int n, int i)
{
	t_cube *cube = get_cube();

	//printf("%d\n",n);

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
	int i;
	char **split;
	int n;

	n = 0;
	split = NULL;
	i = 0;
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
			ft_error(BAD_COLOR);
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
		if(is_whitespace(line[i]) == true)
			i++;
		if(line[i]) //use switch case if norminette allows it
		{
			if(line[i] == 'N' && line[i + 1] == 'O')
				add_path(remove_wspaces(line) + 2, NO);
			if(line[i] == 'S' && line[i + 1] == 'O')
				add_path(remove_wspaces(line) + 2, SO);
			if(line[i] == 'E' && line[i + 1] == 'A')
				add_path(remove_wspaces(line) + 2, EA);
			if(line[i] == 'W' && line[i + 1] == 'E')
				add_path(remove_wspaces(line) + 2, WE);
			if(line[i] == 'C')
				parse_color_code(remove_wspaces(line) + 1, C);
			if(line[i] == 'F')
				parse_color_code(remove_wspaces(line) + 1, F);
		}
		i++;
	
	}
}
void store_file(t_cube*cube)
{
	read_file(cube);
	
	cube->tokens = ft_split(cube->content,'\n');
	if(!cube->tokens)
		ft_error(MALLOC_ERROR);
	loop_line(cube->tokens[6]);

	printf("here %d\n",get_cube()->c_blue);
	//cube->content = ft_free(cube->content);
	//print_tab(cube->tokens);
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