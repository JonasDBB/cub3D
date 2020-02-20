/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 11:00:22 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 11:10:42 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	drawmap(t_var *var, t_data *img, t_minimap *mini)
{
	int	j;

	mini->x = var->width - (mini->maxsqw * mini->sqwidth + mini->offset);
	j = (int)var->player.pos.x - 5;
	if (j < 0)
		j = 0;
	if (j > var->map.maxw - mini->maxsqw)
		j = var->map.maxw - mini->maxsqw;
	while (mini->x < var->width - mini->offset)
	{
		if (var->map.maparray[mini->i][j] == 0 ||
			var->map.maparray[mini->i][j] == 2)
			pxdraw(*img, mini->x, mini->y, 0xFFFFFF);
		if (mini->i == (int)var->player.pos.y && j == (int)var->player.pos.x)
			pxdraw(*img, mini->x, mini->y, 0xFF0000);
		if (var->map.maparray[mini->i][j] == 1)
			pxdraw(*img, mini->x, mini->y, 0x000000);
		mini->x++;
		if ((mini->x - (var->width - (mini->maxsqw *
			mini->sqwidth + mini->offset))) % mini->sqwidth == 0)
			j++;
	}
	mini->y++;
	if (mini->y % mini->sqwidth == 0)
		mini->i++;
}

void		drawminimap(t_var *var, t_data *img)
{
	t_minimap	mini;

	mini.offset = var->width / var->mapscale > var->height / var->mapscale ?
					var->height / var->mapscale : var->width / var->mapscale;
	mini.sqwidth = mini.offset / 2;
	mini.y = mini.offset;
	mini.maxsqh = var->map.h > 11 ? 11 : var->map.h;
	mini.maxsqw = var->map.maxw > 11 ? 11 : var->map.maxw;
	mini.i = (int)var->player.pos.y - 5;
	if (mini.i > var->map.h - mini.maxsqh)
		mini.i = var->map.h - mini.maxsqh;
	if (mini.i < 0)
		mini.i = 0;
	while (mini.y < mini.maxsqh * mini.sqwidth + mini.offset)
		drawmap(&*var, &*img, &mini);
}
