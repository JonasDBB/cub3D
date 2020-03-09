/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 19:47:02 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/09 15:33:28 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		pxdraw(t_data data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bpp / 8));
	*(unsigned int*)dst = (unsigned int)color;
}

static void	preptex(t_var *var, t_cast *caster, t_intcrd *tex, t_data texture)
{
	if (caster->side == 0)
		caster->wallx = var->player.pos.y + caster->wall_d * caster->raydir.y;
	else
		caster->wallx = var->player.pos.x + caster->wall_d * caster->raydir.x;
	caster->wallx -= floor((caster->wallx));
	tex->x = (int)(caster->wallx * (double)texture.texw);
	if (caster->side == 0 && caster->raydir.x > 0)
		tex->x = texture.texw - tex->x - 1;
	if (caster->side == 1 && caster->raydir.y < 0)
		tex->x = texture.texw - tex->x - 1;
	caster->texstep = 1.0 * texture.texh / caster->lineh;
	caster->texpos = (caster->drawstart - var->height /
						2 + caster->lineh / 2) * caster->texstep;
}

void		drawray(t_var *var, t_data *img, t_cast caster, t_data texture)
{
	int			y;
	t_intcrd	tex;

	y = 0;
	while (y < caster.drawstart)
	{
		pxdraw(*img, caster.x, y, var->input.clrceiling);
		y++;
	}
	preptex(&*var, &caster, &tex, texture);
	while (y <= caster.drawend)
	{
		tex.y = (int)caster.texpos & (texture.texh - 1);
		caster.texpos += caster.texstep;
		caster.clr = *(unsigned int*)(texture.addr +
			(tex.y * texture.line_length + tex.x * (texture.bpp / 8)));
		pxdraw(*img, caster.x, y, caster.clr);
		y++;
	}
	while (y < var->height)
	{
		pxdraw(*img, caster.x, y, var->input.clrfloor);
		y++;
	}
}

static void	createimgs(t_var *var, t_data *img, t_data *youdied)
{
	var->dead = 1;
	img->img = mlx_new_image(var->mlx, var->width, var->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
									&img->line_length, &img->endian);
	youdied->img = mlx_png_file_to_image(var->mlx, "./pics/youdied.png",
									&youdied->texw, &youdied->texh);
	youdied->addr = mlx_get_data_addr(youdied->img, &youdied->bpp,
									&youdied->line_length, &youdied->endian);
}

t_data		deathscreen(t_var *var)
{
	t_data			img;
	t_intcrd		c;
	t_data			youdied;
	unsigned int	clr;
	t_intcrd		tex;

	createimgs(*&var, &img, &youdied);
	c.y = 0;
	while (c.y < var->height)
	{
		c.x = 0;
		tex.y = (int)((((c.y * youdied.texw) / var->height)
								* youdied.texh) / youdied.texw);
		while (c.x < var->width)
		{
			tex.x = (int)((((c.x * youdied.texh) /
						var->width) * youdied.texw) / youdied.texh);
			clr = *(unsigned int*)(youdied.addr + (tex.y * youdied.line_length
									+ tex.x * (youdied.bpp / 8)));
			pxdraw(img, c.x, c.y, clr);
			c.x++;
		}
		c.y++;
	}
	return (img);
}
