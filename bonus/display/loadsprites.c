/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/06 00:40:22 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	loadsprites(t_display *display)
{
	display->spritecounted = 0;
	countsprite(display);
	if (display->spritecounted != 0)
	{
		if ((display->sprite = mlx_xpm_file_to_image(display->mlx_ptr,
			display->spritepwd, &display->widthtext[5],
			&display->heighttext[5])))
			display->ptr[5] = mlx_get_data_addr(display->sprite,
			&(display->bpp2[5]), &(display->s_line2[5]), &(display->ed2[5]));
		if ((display->sprite2 = mlx_xpm_file_to_image(display->mlx_ptr,
		"./textures/ghost.xpm", &display->widthtext[10],
		&display->heighttext[10])))
			display->ptr[10] = mlx_get_data_addr(display->sprite2,
			&(display->bpp2[10]), &(display->s_line2[10]), &(display->ed2[10]));
		display->spritex = malloc(display->spritecounted * sizeof(int));
		display->spritey = malloc(display->spritecounted * sizeof(int));
		display->spritedist = malloc(display->spritecounted * sizeof(double));
		display->spritenum = malloc(display->spritecounted * sizeof(int));
		display->zbuffer = malloc((display->r1 + 1) * sizeof(double));
		countsprite(display);
	}
}

void	countsprite(t_display *display)
{
	int	sprites;
	int spritenum;

	sprites = 0;
	display->indexdey = 0;
	display->indexdex = 0;
	while (display->indexdex < display->mapy)
	{
		spritenum = display->map[display->indexdex][display->indexdey];
		if (spritenum == '2' || spritenum == '3' || spritenum == 'k')
		{
			getinfosprite(display, sprites, spritenum);
			sprites++;
		}
		display->indexdey++;
		if (display->indexdey == display->mapx)
		{
			display->indexdey = 0;
			display->indexdex++;
		}
	}
	display->spritecounted = sprites;
}

void	getinfosprite(t_display *display, int sprites, int spritenum)
{
	if (display->spritecounted != 0)
	{
		display->spritex[sprites] = display->indexdey;
		display->spritey[sprites] = display->indexdex;
		display->spritenum[sprites] = spritenum;
	}
}