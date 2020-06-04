/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 16:07:32 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/02 16:44:07 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	getdist(t_var *var, t_cast
	*caster, t_coord *side_d, t_coord delta_d)
{
	if (caster->raydir.x < 0)
	{
		caster->step.x = -1;
		side_d->x = (var->player.pos.x - caster->loc.x) * delta_d.x;
	}
	else
	{
		caster->step.x = 1;
		side_d->x = (caster->loc.x + 1.0 - var->player.pos.x) * delta_d.x;
	}
	if (caster->raydir.y < 0)
	{
		caster->step.y = -1;
		side_d->y = (var->player.pos.y - caster->loc.y) * delta_d.y;
	}
	else
	{
		caster->step.y = 1;
		side_d->y = (caster->loc.y + 1.0 - var->player.pos.y) * delta_d.y;
	}
}

static int	findhit(t_var *var, t_cast *caster,
	t_coord *side_d, t_coord delta_d)
{
	if (side_d->x < side_d->y)
	{
		side_d->x += delta_d.x;
		caster->loc.x += caster->step.x;
		caster->side = 0;
	}
	else
	{
		side_d->y += delta_d.y;
		caster->loc.y += caster->step.y;
		caster->side = 1;
	}
	if (var->map.maparray[caster->loc.y][caster->loc.x] == 1)
		return (1);
	return (0);
}

static void	getheight(t_var *var, t_cast *caster)
{
	if (caster->side == 0)
		caster->wall_d = (caster->loc.x - var->player.pos.x +
					(1 - caster->step.x) / 2) / caster->raydir.x;
	else
		caster->wall_d = (caster->loc.y - var->player.pos.y +
					(1 - caster->step.y) / 2) / caster->raydir.y;
	caster->lineh = (int)(var->height / caster->wall_d);
	caster->drawstart = -caster->lineh / 2 + var->height / 2;
	if (caster->drawstart < 0)
		caster->drawstart = 0;
	caster->drawend = caster->lineh / 2 + var->height / 2;
	if (caster->drawend >= var->height)
		caster->drawend = var->height - 1;
}

static void	choosewall(t_var *var, t_data *img, t_cast caster)
{
	if (caster.side == 1 && caster.raydir.y < 0)
		drawray(&*var, &*img, caster, var->tex.so);
	if (caster.side == 1 && caster.raydir.y > 0)
		drawray(&*var, &*img, caster, var->tex.no);
	if (caster.side == 0 && caster.raydir.x < 0)
		drawray(&*var, &*img, caster, var->tex.ea);
	if (caster.side == 0 && caster.raydir.x > 0)
		drawray(&*var, &*img, caster, var->tex.we);
}

void		drawimg(t_var *var, t_data *img)
{
	t_cast		caster;
	t_coord		camera;
	t_coord		delta_d;
	t_coord		side_d;

	caster.x = 0;
	while (caster.x < var->width)
	{
		camera.x = 2 * caster.x / (double)var->width - 1;
		caster.raydir.x = var->player.dir.x + var->player.plane.x * camera.x;
		caster.raydir.y = var->player.dir.y + var->player.plane.y * camera.x;
		caster.loc.x = (int)var->player.pos.x;
		caster.loc.y = (int)var->player.pos.y;
		delta_d.x = fabs(1 / caster.raydir.x);
		delta_d.y = fabs(1 / caster.raydir.y);
		getdist(&*var, &caster, &side_d, delta_d);
		while (!findhit(&*var, &caster, &side_d, delta_d))
			;
		getheight(&*var, &caster);
		choosewall(&*var, &*img, caster);
		var->zbuffer[caster.x] = caster.wall_d;
		caster.x++;
	}
}
