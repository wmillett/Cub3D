#include "cub3d.h"

// static void	ft_mchook(mlx_key_data_t k, void *param)
// {
// 	t_map	*gpack;
// 	int		move;

// 	gpack = param;
// 	if (k.key == MLX_KEY_D && k.action == 1)
// 		move = 'R';
// 	if (k.key == MLX_KEY_A && k.action == 1)
// 		move = 'L';
// 	if (k.key == MLX_KEY_W && k.action == 1)
// 		move = 'U';
// 	if (k.key == MLX_KEY_S && k.action == 1)
// 		move = 'D';
// 	if (move && k.action == 1)
// 		;
// 	if (k.key == MLX_KEY_ESCAPE && k.action == 1)
// 	{
// 		mlx_terminate(gpack->mlx);
// 		// leave(gpack);
// 	}
// }





int	mlx_start(t_cube *cube)
{
	//printf("%s %s %s %s\n",cube->no_path,cube->so_path,cube->ea_path,cube->we_path);
	cube->cubmlx->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "CUB3D by TDA-3D", true);
	if(!cube->cubmlx->mlx)
		return 1; 
	cube->cubmlx->image = mlx_new_image(cube->cubmlx->mlx,SCREENWIDTH,SCREENHEIGHT);
	if(!cube->cubmlx->image)
		return 1;
	if(mlx_image_to_window(cube->cubmlx->mlx,cube->cubmlx->image,SCREENWIDTH,SCREENHEIGHT) == ERROR)
		return 1;
	cube->cubmlx->south_text = mlx_load_png(cube->so_path);
	if(!cube->cubmlx->south_text)
		return 1;
	cube->cubmlx->north_text = mlx_load_png(cube->no_path);
	if(!cube->cubmlx->north_text)
		return 1;
	cube->cubmlx->east_text = mlx_load_png(cube->ea_path);
	if(!cube->cubmlx->east_text)
		return 1;
	cube->cubmlx->west_text = mlx_load_png(cube->we_path);
	if(!cube->cubmlx->west_text)
		return 1;
	
	//mlx_key_hook(gpack->mlx, &ft_mchook, gpack);
	mlx_loop(cube->cubmlx->mlx);
	mlx_terminate(cube->cubmlx->mlx);

	return (EXIT_SUCCESS);
}



