#include "cub3d.h"



 void	key_hook(mlx_key_data_t keydata, void *param)
 {
 	(void)param;

 	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
 		printf("w\n");	//some code
 	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		printf("d\n");
 	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
 			|| keydata.action == MLX_REPEAT))
 		printf("s\n");//some code
 	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
 			|| keydata.action == MLX_REPEAT))
		printf("a\n");
 }
	/*
    if (keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if (keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
}
*/


void set_raycast_vars(t_raycast*rc)
{
	rc->pos_x = get_cube()->start_x;
	rc->pos_y = get_cube()->start_y;
	rc->dir_x = 1;
	rc->dir_y = 0;
	rc->plane_x = 0;
	rc->plane_y = 0.66;


}

void raycasting_loop(void *arg)
{
	t_cube	*cube;
	t_raycast *rc;
	int x;
	int y;

	cube = (t_cube*)arg;
	rc = cube->raycast;
	y = 0;
	x = 0;
	while(x < SCREENWIDTH)
	{
		rc->camera_x = 2 * x / (double)SCREENWIDTH - 1;
        rc->ray_dir_x = rc->dir_x + rc->plane_x * rc->camera_x;
        rc->ray_dir_y = rc->dir_y + rc->plane_y * rc->camera_x;
	
	 	rc->map_x = (int)rc->pos_x;
        rc->map_y = (int)rc->pos_y;

	    rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
        rc->delta_dist_y = fabs(1 / rc->ray_dir_y);

		if (rc->ray_dir_x < 0) 
		{
			rc->step_x = -1;
			rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
		} 
		else 
		{
			rc->step_x = 1;
			rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
		}
		if (rc->ray_dir_y < 0)
		{
			rc->step_y = -1;
			rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
		} 
		else 
		{
			rc->step_y = 1;
			rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
		}
		
	// DDA
 	rc->hit = 0; 
	rc->side = 0;


      while (rc->hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (rc->side_dist_x < rc->side_dist_y)
        {
          rc->side_dist_x += rc->delta_dist_x;
          rc->map_x += rc->step_x;
          rc->side = 0;
        }
        else
        {
          rc->side_dist_y += rc->delta_dist_y;
          rc->map_y += rc->step_y;
          rc->side = 1;
        }
        //Check if ray has hit a wall
		
        if (cube->map[rc->map_y][rc->map_x] == '1') 
			rc->hit = 1;
      } 

		//Calculate distance projected on camera direction
	

		if(rc->side == 0) 
			rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
		else          
			rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);

        // Calculate height of line to draw on screen (you need to implement your own height calculation logic)
        rc->line_height = (int)(SCREENHEIGHT / rc->perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        rc->draw_start = -rc->line_height / 2 + SCREENHEIGHT / 2;
        if (rc->draw_start < 0) 
		{
            rc->draw_start = 0;
        }
        rc->draw_end = rc->line_height / 2 + SCREENHEIGHT / 2;
        if (rc->draw_end >= SCREENHEIGHT) 
		{
            rc->draw_end = SCREENHEIGHT - 1;
        }

		//------------------------------------------------------------------

		y = rc->draw_start;
		while(y < rc->draw_end) //change with texture code
		{
			mlx_put_pixel(cube->cubmlx->img_buf,x,y,0x0000ffff); 
			y++;
		}
		x++;
	}
	usleep(1000);
}	