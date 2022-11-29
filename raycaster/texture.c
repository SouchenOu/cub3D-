/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:25:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 22:29:10 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calcul_texture_pixls(t_struct *cub)
{
	cub->tmp.textureOffsetX /= cub->scaleHeight;
	cub->tmp.textureOffsetX -= floor(cub->tmp.textureOffsetX);
	cub->tmp.textureOffsetX *= cub->texture->img_width;
	cub->tmp.o = cub->tmp.wallTopPixel;
	while (cub->tmp.o < cub->tmp.wallBottomPixel)
	{
		cub->tmp.distanceFromTop = cub->tmp.o + ((cub->tmp.len_n / 2) \
				- (W_HEIGHT / 2));
		if (cub->tmp.distanceFromTop < 0)
			cub->tmp.distanceFromTop = 0;
		cub->tmp.textureOffsetY = (cub->tmp.distanceFromTop) * \
				((double)cub->texture->img_height / cub->tmp.len_n);
		cub->tmp.textureOffsetY = floor(cub->tmp.textureOffsetY);
		set_texturecolor(cub);
		cub->addr[(W_WIDTH * cub->tmp.o) + cub->tmp.i_n] = \
											cub->tmp.texturecolor;
		cub->check_test = 1;
		cub->tmp.o++;
	}
}

void	set_texturecolor(t_struct *cub)
{
	cub->tmp.texturecolor = 0;
	if (cub->ray.check == 1)
	{
		if (cub->ray.rayAngle < (M_PI / 2) || cub->ray.rayAngle > \
				((3 * M_PI) / 2))
			cub->tmp.texturecolor = cub->texture[0].data[(int) \
			(cub->texture[0].img_width * cub->tmp.textureOffsetY) + \
			(int)cub->tmp.textureOffsetX];
		else
			cub->tmp.texturecolor = cub->texture[1].data[(int) \
				(cub->texture[1].img_width * cub->tmp.textureOffsetY) + \
				(int)cub->tmp.textureOffsetX];
	}
	else if (cub->ray.check == 2)
	{
		if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
			cub->tmp.texturecolor = cub->texture[3].data[(int) \
			(cub->texture[3].img_width * cub->tmp.textureOffsetY) + \
			(int)cub->tmp.textureOffsetX];
		else
			cub->tmp.texturecolor = cub->texture[2].data[(int) \
				(cub->texture[2].img_width * cub->tmp.textureOffsetY) + \
				(int)cub->tmp.textureOffsetX];
	}
}
