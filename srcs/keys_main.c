/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:55:19 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 14:53:48 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotatevector(t_coord *vector, double speed)
{
	double oldx;

	oldx = vector->x;
	vector->x = vector->x * cos(speed) - vector->y * sin(speed);
	vector->y = oldx * sin(speed) + vector->y * cos(speed);
}

int			keyspress(int keycode, t_var *var)
{
	if (keycode == 53)
		key_escape(&*var);
	if (keycode == 0)
		var->pressed[0] = 1;
	if (keycode == 1)
		var->pressed[1] = 1;
	if (keycode == 2)
		var->pressed[2] = 1;
	if (keycode == 13)
		var->pressed[3] = 1;
	if (keycode == 124)
		var->pressed[4] = 1;
	if (keycode == 123)
		var->pressed[5] = 1;
	if (keycode == 49)
	{
		var->player.spdmove = 0.15;
		var->player.spdrot = 0.08;
	}
	return (1);
}

int			key_escape(t_var *var)
{
	mlx_destroy_window(var->mlx, var->win);
	sysend();
	exit(1);
	return (0);
}

void		key_left(t_var *var)
{
	rotatevector(&(var->player.dir), var->player.spdrot);
	rotatevector(&(var->player.plane), var->player.spdrot);
	var->player.moved = 1;
}

void		key_right(t_var *var)
{
	rotatevector(&(var->player.dir), -1 * var->player.spdrot);
	rotatevector(&(var->player.plane), -1 * var->player.spdrot);
	var->player.moved = 1;
}
