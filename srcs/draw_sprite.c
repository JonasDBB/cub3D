/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 12:14:37 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 14:53:23 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	drawlengths(t_var *var, t_sprvars *sprvars)
{
	sprvars->spr_h = abs((int)(var->height / (sprvars->transform.y)));
	sprvars->drawstart.y = -sprvars->spr_h / 2 + var->height / 2;
	if (sprvars->drawstart.y < 0)
		sprvars->drawstart.y = 0;
	sprvars->drawend.y = sprvars->spr_h / 2 + var->height / 2;
	if (sprvars->drawend.y >= var->height)
		sprvars->drawend.y = var->height - 1;
	sprvars->spr_w = abs((int)(var->height / (sprvars->transform.y)));
	sprvars->drawstart.x = -sprvars->spr_w / 2 + sprvars->spr_screenx;
	if (sprvars->drawstart.x < 0)
		sprvars->drawstart.x = 0;
	sprvars->drawend.x = sprvars->spr_w / 2 + sprvars->spr_screenx;
	if (sprvars->drawend.x >= var->width)
		sprvars->drawend.x = var->width - 1;
}

static void	startvalues(t_var *var, t_sprvars *sprvars, int i)
{
	sprvars->current.x = var->sprites.locs[var->sprites.order[i]].x
								- var->player.pos.x;
	sprvars->current.y = var->sprites.locs[var->sprites.order[i]].y
								- var->player.pos.y;
	sprvars->invdet = 1.0 / (var->player.plane.x * var->player.dir.y
								- var->player.dir.x * var->player.plane.y);
	sprvars->transform.x = sprvars->invdet * (var->player.dir.y *
				sprvars->current.x - var->player.dir.x * sprvars->current.y);
	sprvars->transform.y = sprvars->invdet * (-(var->player.plane.y) *
				sprvars->current.x + var->player.plane.x * sprvars->current.y);
	sprvars->spr_screenx = (int)((var->width / 2) *
				(1 + sprvars->transform.x / sprvars->transform.y));
}

static void	castline(t_var *var, t_data *img, t_data texture, t_sprvars sprvars)
{
	int				y;
	int				d;
	unsigned int	clr;

	sprvars.tex.x = (int)(256 * (sprvars.line - (-sprvars.spr_w
			/ 2 + sprvars.spr_screenx)) * texture.texw / sprvars.spr_w) / 256;
	if (sprvars.transform.y > 0 && sprvars.line > 0 && sprvars.line < var->width
			&& sprvars.transform.y < var->zbuffer[sprvars.line])
	{
		y = sprvars.drawstart.y;
		while (y < sprvars.drawend.y)
		{
			d = (y) * 256 - var->height * 128 + sprvars.spr_h * 128;
			sprvars.tex.y = ((d * texture.texh) / sprvars.spr_h) / 256;
			clr = *(unsigned int*)(texture.addr + (sprvars.tex.y
				* texture.line_length + sprvars.tex.x * (texture.bpp / 8)));
			if (clr != 0x00000000)
				pxdraw(*img, sprvars.line, y, clr);
			y++;
		}
	}
}

void		drawsprites(t_var *var, t_data *img, t_data texture)
{
	int			i;
	t_sprvars	sprvars;

	i = var->sprites.count - 1;
	while (i >= 0)
	{
		startvalues(*&var, &sprvars, i);
		drawlengths(*&var, &sprvars);
		sprvars.line = sprvars.drawstart.x;
		while (sprvars.line < sprvars.drawend.x)
		{
			castline(*&var, *&img, texture, sprvars);
			sprvars.line++;
		}
		i--;
	}
}
