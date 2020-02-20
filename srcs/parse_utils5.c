/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:26:12 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/19 12:54:36 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floodfill(t_var *var, int x, int y)
{
	if (!var->map.valid)
		errormsg("invalid map");
	if (x < 0 || x >= var->map.maxw || y < 0 || y >= var->map.h)
	{
		var->map.valid = 0;
		return ;
	}
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

void	validmap(t_var var)
{
	int	x;
	int	y;

	if (var.player.pos.x == -1)
		errormsg("no player");
	var.map.valid = 1;
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

int		digits(unsigned long n)
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

void	errormsg(char *reason)
{
	write(1, "Error\n", 6);
	ft_putstr_fd("reason: ", 1);
	ft_putstr_fd(reason, 1);
	write(1, "\n", 1);
	sysend();
	exit(0);
}

void	sysend(void)
{
	system("leaks a.out >> leaks.txt");
	system("grep \"total leaked bytes\" leaks.txt");
	system("rm leaks.txt");
}
