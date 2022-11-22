/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/22 19:43:01 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_struct *ptr, int x, int y, unsigned int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		dst = (char *)ptr->addr + (y * ptr->line_length + x
				* (ptr->bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

int ft_count_height(t_struct *cub)
{
    int len;
    int i;
    int j;

    i = 0;
    len = 0;
    while (cub->my_map[i])
    {
        j = 0;
        while (cub->my_map[i][j])
        {
          if (j == 0)
            len++;
          j++;  
        }
      i++;  
    }
   return (len); 
}

void    draw_cub(t_struct *ptr, int x, int y, int color)
{
    int start_x;
    int start_y;
    int     i;
    int     j;

        
        start_x =  x * ptr->mini_map.mini_scaleWidth;
        start_y =  y * ptr->mini_map.mini_scaleHeight;
        i = start_y;
        j = start_x;
        while (i < start_y + ptr->mini_map.mini_scaleHeight)
        {
            j =  start_x;
            while (j < start_x + ptr->mini_map.mini_scaleWidth)
            {
                my_mlx_pixel_put(ptr, j, i, color);
                j++;
            }
        i++;
    }
}

void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    int     len;

    y = 0;
    len = 0;
     int xx = (cub->player.position_x/ cub->scaleWidth) * cub->mini_map.mini_scaleWidth;
    int yy = (cub->player.position_y / cub->scaleHeight) * cub->mini_map.mini_scaleHeight;
    drawRaysOfplyer(cub, cub->player.position_x, cub->player.position_y , 0xFFFF0F); 
    while (cub->my_map[y])
    {
        x = 0;
        while (cub->my_map[y][x])
        {
           if (cub->my_map[y][x] == '1')
               draw_cub(cub, x, y, 0xFFF0000);
            if (cub->my_map[y][x] == '0')
                draw_cub(cub, x, y, 0);
            x++;
        }
        y++;
    }
    drawRaysOfplyer_mini(cub, xx, yy , 0xFFFF0F);     
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}

void player_position(t_struct *cub){
    int i = 0;
    int j = 0;
  
    cub->scaleHeight = W_HEIGHT/ cub->heightof_minimap;
    cub->scaleWidth = W_WIDTH/ cub->width;
    cub->player.rottSpeed = 0.174533;
    cub->player.walkDrctn = 0;
    cub->numOfRays = W_WIDTH;
   while (cub->my_map[i])
   {
        j = 0;
        while(cub->my_map[i][j])
        {
            if (cub->my_map[i][j] == 'E'|| cub->my_map[i][j] == 'N' || cub->my_map[i][j] == 'S' || cub->my_map[i][j] == 'W')
            {
                cub->player.position_x = j * cub->scaleWidth;
                cub->player.position_y = i * cub->scaleHeight;
                cub->mini_map.mini_scaleWidth = (cub->scaleWidth / 4);
                cub->mini_map.mini_scaleHeight = (cub->scaleHeight / 4);
                return ;
            }
            j++;
        }
        i++;
   } 
}

int	player_move(int key, t_struct *cub)
{ 
    cub->player.walkDrctn = 0;
	if (key == 1){
        cub->player.walkDrctn = -1;
		check_nextSteep(cub);
    }
	else if (key == 13){
        cub->player.walkDrctn = 1;
       check_nextSteep(cub);
    }
	else if (key == 2){
        cub->player.walkDown = 1;
		check_downSteep(cub);
    }
	else if (key == 0){
        cub->player.walkDown= -1;
		check_downSteep(cub);
    }
    else if (key == 124)
        cub->player.rottAngle += cub->player.rottSpeed;
	else if (key == 123)
        cub->player.rottAngle -= cub->player.rottSpeed;
    mlx_destroy_image(cub->mlx_ptr, cub->img);
    cub->img = mlx_new_image(cub->mlx_ptr, W_WIDTH, W_HEIGHT);
    ft_draw_map(cub);
    return (0);
}

void check_nextSteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    new_y = cub->player.position_y + (sin(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}

void check_downSteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 4));
    new_y = cub->player.position_y + (sin(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 4));
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}

void directionOfPlayer(t_struct *cub)
{
    int gred_y = floor(cub->player.position_y/cub->scaleHeight);
    int gred_x = floor(cub->player.position_x/cub->scaleWidth);
    if (cub->my_map[gred_y][gred_x] == 'N')
        cub->player.rottAngle = M_PI / 2;
    if (cub->my_map[gred_y][gred_x] == 'S')
        cub->player.rottAngle = M_PI * (3/ 2);
    if (cub->my_map[gred_y][gred_x] == 'W')
        cub->player.rottAngle = M_PI;
    if (cub->my_map[gred_y][gred_x] == 'E')
        cub->player.rottAngle = 0;
}