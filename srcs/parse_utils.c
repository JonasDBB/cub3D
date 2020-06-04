/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:26:12 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/02 14:20:32 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	floodfill(t_var *var, int x, int y)
{
	if (x < 0 || x >= var->map.maxw || y < 0 || y >= var->map.h)
		errormsg("invalid map");
	if (var->map.arraycpy[y][x] == -2)
		errormsg("open spaces in map");
	if (var->map.arraycpy[y][x] != 0 && var->map.arraycpy[y][x] != 2)
		return ;
	var->map.arraycpy[y][x] = 9;
	floodfill(var, x + 1, y);
	floodfill(var, x - 1, y);
	floodfill(var, x, y + 1);
	floodfill(var, x, y - 1);
	floodfill(var, x + 1, y + 1);
	floodfill(var, x - 1, y - 1);
	floodfill(var, x - 1, y + 1);
	floodfill(var, x + 1, y - 1);
}

void		validmap(t_var var)
{
	int	x;
	int	y;

	if (var.player.pos.x == -1)
		errormsg("no player");
	floodfill(&var, var.player.pos.x, var.player.pos.y);
	y = 0;
	while (y < var.map.h)
	{
		x = 0;
		while (var.map.arraycpy[y][x] != -1)
		{
			if (var.map.arraycpy[y][x] == 0 || var.map.arraycpy[y][x] == 2)
				var.map.maparray[y][x] = 1;
			x++;
		}
		y++;
	}
}

int			mapline(t_var var)
{
	int	i;

	i = 0;
	while (var.map.line[i] == ' ')
		i++;
	if (var.map.line[i] >= '0' && var.map.line[i] <= '2')
		return (1);
	return (0);
}

void		getwidth(t_var *var)
{
	int	maxw;
	int	i;

	maxw = 0;
	i = 0;
	while (var->map.line[i])
	{
		maxw++;
		i++;
	}
	if (maxw > var->map.maxw)
		var->map.maxw = maxw;
	var->map.h++;
	free(var->map.line);
}

int			digits(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}
