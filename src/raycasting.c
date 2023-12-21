#include "cub3d.h"



// static void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	(void)param;

// 	t_cube *cube = get_cube();
// 	// if (keydata.key == MLX_KEY_ESCAPE)
// 	// 	mlx_close_window(map->m_pack->mlx);

// 	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		{
// 			//some code

// 		}
// 	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		{
// 			//some code

// 		}
// 	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
// 			|| keydata.action == MLX_REPEAT))
// 		{
// 			//some code

// 		}
// 	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
// 			|| keydata.action == MLX_REPEAT))
// 		{
// 			//some code

// 		}
// }

void raycasting_loop(void *arg)
{
	(void)arg;
	t_cube	*cube = get_cube();
	double posX = cube->start_x;
	double posY = cube->start_y; 
  	double dirX = 1; //change depending intial orientation
	double dirY = 0; 
 	double planeX = 0;
	double planeY = 0.66; 

	//double moveSpeed = 10;

	int x;

	x = 0;
	while(x < SCREENWIDTH)
	{
		double cameraX = 2 * x / (double)SCREENWIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
	
	 	int mapX = (int)posX;
        int mapY = (int)posY;

	    double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

		int stepX;
		int stepY;
 		double sideDistX;
        double sideDistY;

		if (rayDirX < 0) 
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		} 
		else 
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		} 
		else 
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		
	// DDA
 	int hit = 0; 
	int side = 0;


      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
		
        if (cube->map[mapY][mapX] == '1') 
			hit = 1;
      } 

		//Calculate distance projected on camera direction
		double perpWallDist;

		if(side == 0) 
			perpWallDist = (sideDistX - deltaDistX);
		else          
			perpWallDist = (sideDistY - deltaDistY);

        // Calculate height of line to draw on screen (you need to implement your own height calculation logic)
        int lineHeight = (int)(SCREENHEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawStart < 0) 
		{
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawEnd >= SCREENHEIGHT) 
		{
            drawEnd = SCREENHEIGHT - 1;
        }

		//------------------------------------------------------------------

		int y = drawStart;
		while(y < drawEnd) //change with texture code
		{
			mlx_put_pixel(cube->cubmlx->img_buf,x,y,0x0000ffff); 
			y++;
		}

		//------------------------------------------------------------------

		
		//texture part
		//movement hook
		//colisions

		x++;
	}
	usleep(1000);
}	