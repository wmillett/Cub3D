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





int	ft_window(t_cube *cube)
{
	//printf("w %d h %d\n",cube->width, cube->height);
	cube->cubmlx->mlx = mlx_init(SCREENWIDTH * 64, SCREENHEIGHT * 64, 
		"CUB3D by TDA-3D", true);
	if(!cube->cubmlx)
		return 1; //error here

	//mlx_key_hook(gpack->mlx, &ft_mchook, gpack);
	mlx_loop(cube->cubmlx->mlx);
	mlx_terminate(cube->cubmlx->mlx);

	return (EXIT_SUCCESS);
}



