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

int is_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
	|| c == 'S' || c == 'W' || c == 'E');
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
	while(line[i]) //can remove that loop
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

int find_map_start(char *content)
{
	int i;
	int start;

	i = 0;
	start = 0;
	while(content[i])
	{
		if(content[i] == '\n')
		{
			i++;
			start = i;
			//printf("%d\n", i);
			while(content[i] && is_whitespace(content[i]) == true && content[i] != 10)
				i++;
			//printf("%d\n", i);
			if(content[i] == '0' || content[i] == '1')
				return start; 
		}
		else
			i++;
	}
	return -1;
}

void validate_map(char *content)
{
	static int count = 0;
	int i;

	
	i = 0;
	while(content[i]) 
	{
		if(count > 1)
			ft_error(MANY_POS);
		if(content[i] == 'N'|| content[i]  == 'S' 
			|| content[i]  == 'W' || content[i]  == 'E')
			count++;
		if(is_whitespace(content[i]) == false && (content[i] != '1' && content[i] != '0' 
		&& content[i] != 'N' && content[i] != 'S' && content[i]  != 'W' && content[i] != 'E'))
			ft_error(WEIRD_CHAR);
		i++;
	}
	if(count == 0)
		ft_error(NO_POS);

}
void tokens_loop(char **tokens)
{
	t_cube *cube;
	int i;
	
	cube = get_cube();
	cube->found_map = false;
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
	// include what is on same line before start map
	// flood fill
}


char** get_map2(char *content)
{
	int count = 0;
	//int len = 0;
	int max = 0;
	char **split;
	//char *substr;
	int i;

	i = 0;
	split = NULL;
	int tabcount = 0; 
	while(content[i])
	{
		//len = i;
		tabcount = 0;
		while(content[i] && content[i] != '\n')
		{
			if(content[i] == '\t')
			{
				tabcount += 3 - ((tabcount  ) % 4);
				//len -= tabcount - 1; 

			}
			tabcount++;
			i++;
		}
		if(content[i] == '\n')
			count++;
		//len = tabcount - len;
		if(tabcount > max)
			max = tabcount;
		i++;
		
	}
	//printf("tab %d\n",tabcount);
	split = malloc(sizeof(char*) * (count + 2));
	split[count + 1] = NULL;
	printf("count: %d len: %d\n",count,max);
	
	i = 0;
	while(i < count + 1)
	{
		split[i] = malloc(sizeof(char) * (max + 1));
		split[i][max] = 0;
		ft_memset(split[i],'-',max);
		i++;
	}
	print_tab(split);
	printf("\n");
	i = 0;
	int j = 0;
	max = 0;
//	len = 0;
	while(content[i])
	{
		
		j = 0;
		tabcount = 0;
		while(content[i] && content[i] != '\n')
		{
			if(content[i] == '\t')
				j += (4 - ((j ) % 4) -1 ); 
			if(is_whitespace(content[i]) == false)
				split[max][j] = content[i];
			j++;
			i++;
			
		}
		if(content[i] == '\n')
			max++;
		i++;
	}
	return split;
}


	//tab == 4 spaces
	/*int j = 0;
	while(content[i])
	{
		
		
		while(content[i] && content[i] != '\n')
		{
			if(is_whitespace(content[i]) && content[i] != '\n')
				content[i] = 'x';
			
			i++;
		}
		while()
		
		i++;
	}*/



void flood_fill(t_cube *cube, int y, int x)
{
	if(cube->map[y][x] == '-')
		ft_error(MAP_OPEN);
	if(cube->map[y][x] == '0')
		cube->map[y][x] = 'X';
	if(cube->map[y][x + 1] && cube->map[y][x + 1] != '1' && cube->map[y][x + 1] != 'X')
		flood_fill(cube,y,x+1);
	if(cube->map[y][x - 1] && cube->map[y][x - 1]!= '1' && cube->map[y][x - 1] != 'X')
		flood_fill(cube,y,x-1);
	if(cube->map[y + 1][x] && cube->map[y + 1][x] != '1' && cube->map[y + 1][x] != 'X')
		flood_fill(cube,y + 1,x);
	if(cube->map[y - 1][x] && cube->map[y - 1][x] != '1' && cube->map[y - 1][x] != 'X')
		flood_fill(cube,y - 1,x);
	
}

void find_position(char **map)
{
	t_cube *cube = get_cube();
	int y;
	int x;

	x = 0;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(is_map_char(map[y][x]) == true && map[y][x] != '1'
			&& map[y][x] != '0')
			{
				if(map[y][x] == 'N')
					cube->orientation = N;
				if(map[y][x] == 'S')
					cube->orientation = S;
				if(map[y][x] == 'E')
					cube->orientation = E;
				if(map[y][x] == 'W')
					cube->orientation = W;
				cube->start_x = x;
				cube->start_y = y;
				return ;
			}
			
			x++;
		}
		y++;
	}
}
void store_file(t_cube*cube)
{
	read_file(cube);
	
	cube->tokens = ft_split(cube->content,'\n');
	if(!cube->tokens)
		ft_error(MALLOC_ERROR);
	//print_tab(cube->tokens);
	//printf("here: %s\n", cube->tokens[5]);
	
	//tokens_loop(cube->tokens);
	//printf("%s\n",cube->content + find_map_start(cube->content));
	//validate_map(cube->content + find_map_start(cube->content));
	 
	char *map_content = cube->content + find_map_start(cube->content);
	
	//print_tab(get_map2(map_content));
	cube->map = get_map2(map_content);
	find_position(cube->map);
	printf("enum %d y %d x %d\n", cube->orientation, cube->start_y,cube->start_x);
	flood_fill(cube,cube->start_y,cube->start_x);
	print_tab(cube->map);
	//printf("here %d\n",get_cube()->c_blue);
	//cube->content = ft_free(cube->content);
	//printf("%s\n", remove_wspaces(cube->tokens[0],0));
	//add_path(remove_wspaces(cube->tokens[0],0));

	// flood fill, if a whitespace in playable map, not valid

}



//integrate garbage collector and copy libft mallocedfunctions here

//dont forget to check if map is not bigger than screen size