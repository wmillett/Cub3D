#include "cub3d.h"

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Map representing the environment (1 for wall, 0 for empty space)
int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// // Player's position and direction


void init_raycasting(t_cube *cube)
{
    cube.pos_x = 1.5;
    cube.pos_y = 1.5;
    cube.dir_x = 1.0;
    cube.dir_y = 0.0;
}







// Raycasting function
void castRay(double rayAngle) 
{
    // Ray parameters
    double rayX = playerX;
    double rayY = playerY;
    double rayDirX = playerDirX + sin(rayAngle);
    double rayDirY = playerDirY + cos(rayAngle);

    // Map coordinates
    int mapX = (int)rayX;
    int mapY = (int)rayY;

    // Ray steps
    double sideDistX, sideDistY;
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    int stepX, stepY;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (rayX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - rayX) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (rayY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - rayY) * deltaDistY;
    }

    // DDA (Digital Differential Analyzer) algorithm for raycasting
    while (map[mapX][mapY] == 0) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
        }
    }

    // Calculate distance to the wall
    double perpWallDist;
    if (sideDistX < sideDistY) {
        perpWallDist = (mapX - rayX + (1 - stepX) / 2) / rayDirX;
    } else {
        perpWallDist = (mapY - rayY + (1 - stepY) / 2) / rayDirY;
    }

    // Draw the ray on the screen or perform other actions based on the distance
    // (e.g., draw a column of pixels representing the wall)
    // ...
}

int raycast(t_cube *cube)
{
    double rayAngle;
    size_t i;

    init_raycasting(cube);
    i = 0;
    while (i < 160)
    {
        rayAngle = playerDirX - 0.5 + i * 0.00625;
        castRay(rayAngle);
        i++;
    }
    return 0;
}
