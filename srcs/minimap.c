/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 11:00:22 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/18 13:43:05 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned int	getclr(t_var var, t_minimap mini, int j)
{
	if (mini.i == (int)var.player.pos.y && j == (int)var.player.pos.x)
		return (0xFF0000);
	if (var.map.maparray[mini.i][j] == 0)
		return (0xFFFFFF);
	if (var.map.maparray[mini.i][j] == 2)
		return (0xFFE73C);
	if (var.map.maparray[mini.i][j] == 1 || var.map.maparray[mini.i][j] == -2)
		return (0x000000);
	return (0xFF00FF);
}

static void			drawmap(t_var *var, t_data *img, t_minimap *mini)
{
	int				j;
	unsigned int	clr;

	mini->x = var->width - (mini->maxsqw * mini->sqwidth + mini->offset);
	j = (int)var->player.pos.x - 5;
	if (j < 0)
		j = 0;
	if (j > var->map.maxw - mini->maxsqw)
		j = var->map.maxw - mini->maxsqw;
	while (mini->x < var->width - mini->offset)
	{
		clr = getclr(*var, *mini, j);
		pxdraw(*img, mini->x, mini->y, clr);
		mini->x++;
		if ((mini->x - (var->width - (mini->maxsqw *
			mini->sqwidth + mini->offset))) % mini->sqwidth == 0)
			j++;
	}
	mini->y++;
	if (mini->y % mini->sqwidth == 0)
		mini->i++;
}

static void			drawlife(t_var var, t_data *img)
{
	int				x;
	int				y;
	unsigned int	clr;
	int				redhp;

	y = var.height * 0.9;
	redhp = (var.width * 0.4 / 100) * var.player.hp + (var.width * 0.3) - 1;
	while (y < var.height * 0.95)
	{
		x = var.width * 0.3;
		clr = 0x00FF00;
		while (x < var.width * 0.7)
		{
			if (x > redhp)
				clr = 0xFF0000;
			pxdraw(*img, x, y, clr);
			x++;
		}
		y++;
	}
}

void				drawminimap(t_var *var, t_data *img)
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
	while (mini.y < mini.maxsqh * mini.sqwidth + mini.offset
		&& mini.i < var->map.h)
		drawmap(&*var, &*img, &mini);
	drawlife(*var, &*img);
}
