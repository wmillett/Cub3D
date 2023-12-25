#include "cub3d.h"

void  display_background(t_cube *cube)
{
	int x;
	int y;

	y = 0;
	x = 0;
	while(y < SCREENHEIGHT / 2)
	{
		x = 0;
		while(x < SCREENWIDTH)
		{
			mlx_put_pixel(cube->cubmlx->bg_buf,x,y,cube->cubmlx->floor_color);
			x++;
		}
		y++;
	}
	while(y < SCREENHEIGHT)
	{
		x = 0;
		while(x < SCREENWIDTH)
		{
			mlx_put_pixel(cube->cubmlx->bg_buf,x,y,cube->cubmlx->ceiling_color);
			x++;
		}
		y++;
	}
}

int	translate_color(int r, int g, int b, int alpha)
{
	return (r << 24 | g << 16 | b << 8 | alpha);
}

int	mlx_start(t_cube *cube)
{
	cube->cubmlx->ceiling_color = translate_color(cube->c_red, cube->c_green, cube->c_blue, 255);
	cube->cubmlx->floor_color = translate_color(cube->f_red, cube->f_green, cube->f_blue, 255);
	cube->cubmlx->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "CUB3D by TDA-3D", false);
	if(!cube->cubmlx->mlx)
		return 1; 

	cube->cubmlx->bg_buf = mlx_new_image(cube->cubmlx->mlx,SCREENWIDTH,SCREENHEIGHT);
	if(!cube->cubmlx->bg_buf)
		return 1;
	display_background(cube);
	if(mlx_image_to_window(cube->cubmlx->mlx,cube->cubmlx->bg_buf,0,0) == ERROR)
		return 1;

	cube->cubmlx->img_buf = mlx_new_image(cube->cubmlx->mlx,SCREENWIDTH,SCREENHEIGHT);
	if(!cube->cubmlx->img_buf)
		return 1;
	if(mlx_image_to_window(cube->cubmlx->mlx,cube->cubmlx->img_buf,0,0) == ERROR)
		return 1;

	cube->cubmlx->south_text = mlx_load_png(cube->so_path);
	if(!cube->cubmlx->south_text)
		return 1;
	// cube->cubmlx->north_text = mlx_load_png(cube->no_path);
	// if(!cube->cubmlx->north_text)
	// 	return 1;
	// cube->cubmlx->east_text = mlx_load_png(cube->ea_path);
	// if(!cube->cubmlx->east_text)
	// 	return 1;
	// cube->cubmlx->west_text = mlx_load_png(cube->we_path);
	// if(!cube->cubmlx->west_text)
	// 	return 1;
	set_raycast_vars(cube->raycast);

	//mlx_key_hook(cube->cubmlx->mlx, &key_hook, NULL);
	mlx_loop_hook(cube->cubmlx->mlx,&raycasting_loop,cube);
	mlx_loop(cube->cubmlx->mlx);
	mlx_terminate(cube->cubmlx->mlx);
	//free mlx stuff and add in error function
	return (EXIT_SUCCESS);
}
