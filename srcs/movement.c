/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:26:56 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 14:54:08 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		keysrelease(int keycode, t_var *var)
{
	if (keycode == 0)
		var->pressed[0] = 0;
	if (keycode == 1)
		var->pressed[1] = 0;
	if (keycode == 2)
		var->pressed[2] = 0;
	if (keycode == 13)
		var->pressed[3] = 0;
	if (keycode == 124)
		var->pressed[4] = 0;
	if (keycode == 123)
		var->pressed[5] = 0;
	if (keycode == 49)
	{
		var->player.spdmove = 0.05;
		var->player.spdrot = 0.05;
	}
	return (1);
}

void	movement(t_var *var)
{
	if (var->pressed[0] == 1)
		key_a(&*var);
	if (var->pressed[1] == 1)
		key_s(&*var);
	if (var->pressed[2] == 1)
		key_d(&*var);
	if (var->pressed[3] == 1)
		key_w(&*var);
	if (var->pressed[4] == 1)
		key_left(&*var);
	if (var->pressed[5] == 1)
		key_right(&*var);
}
