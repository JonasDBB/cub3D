/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 15:03:51 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 17:52:45 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_value_at(t_var *var, double y, double x)
{
	return (var->map.maparray[(int)y][(int)x]);
}

void		key_a(t_var *var)
{
	int	value_at;

	value_at = get_value_at(&*var, var->player.pos.y - var->player.plane.y *
							2 * var->player.spdmove, var->player.pos.x);
	if (value_at == 0 || value_at == 2)
		var->player.pos.y -= var->player.plane.y * var->player.spdmove;
	value_at = get_value_at(&*var, var->player.pos.y, var->player.pos.x -
							var->player.plane.x * 2 * var->player.spdmove);
	if (value_at == 0 || value_at == 2)
		var->player.pos.x -= var->player.plane.x * var->player.spdmove;
	var->player.moved = 1;
}

void		key_s(t_var *var)
{
	int	value_at;

	value_at = get_value_at(&*var, var->player.pos.y - var->player.dir.y *
							2 * var->player.spdmove, var->player.pos.x);
	if (value_at == 0 || value_at == 2)
		var->player.pos.y -= var->player.dir.y * var->player.spdmove;
	value_at = get_value_at(&*var, var->player.pos.y, var->player.pos.x -
							var->player.dir.x * 2 * var->player.spdmove);
	if (value_at == 0 || value_at == 2)
		var->player.pos.x -= var->player.dir.x * var->player.spdmove;
	var->player.moved = 1;
}

void		key_d(t_var *var)
{
	int	value_at;

	value_at = get_value_at(&*var, var->player.pos.y + var->player.plane.y *
							2 * var->player.spdmove, var->player.pos.x);
	if (value_at == 0 || value_at == 2)
		var->player.pos.y += var->player.plane.y * var->player.spdmove;
	value_at = get_value_at(&*var, var->player.pos.y, var->player.pos.x +
							var->player.plane.x * 2 * var->player.spdmove);
	if (value_at == 0 || value_at == 2)
		var->player.pos.x += var->player.plane.x * var->player.spdmove;
	var->player.moved = 1;
}

void		key_w(t_var *var)
{
	int	value_at;

	value_at = get_value_at(&*var, var->player.pos.y + var->player.dir.y *
							2 * var->player.spdmove, var->player.pos.x);
	if (value_at == 0 || value_at == 2)
		var->player.pos.y += var->player.dir.y * var->player.spdmove;
	value_at = get_value_at(&*var, var->player.pos.y, var->player.pos.x +
							var->player.dir.x * 2 * var->player.spdmove);
	if (value_at == 0 || value_at == 2)
		var->player.pos.x += var->player.dir.x * var->player.spdmove;
	var->player.moved = 1;
}
