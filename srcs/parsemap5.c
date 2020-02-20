/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap5.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:25:15 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 11:17:51 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setplayer(t_var *var, int i, int j, int k)
{
	if (var->player.pos.x != -1)
		errormsg("too many players");
	var->player.pos.x = j;
	var->player.pos.y = i;
	var->map.maparray[i][j] = 0;
	var->map.arraycpy[i][j] = 0;
	var->map.direction = var->map.line[k];
	setdir(&*var);
}

void	linefinish(t_var *var, int i, int j)
{
	while (j < var->map.maxw)
	{
		var->map.maparray[i][j] = 0;
		var->map.arraycpy[i][j] = 0;
		j++;
	}
	var->map.maparray[i][j] = -1;
	var->map.arraycpy[i][j] = -1;
	free(var->map.line);
}

void	createline(t_var *var, int i)
{
	int	j;
	int	k;

	var->map.maparray[i] = malloc(sizeof(int) * var->map.maxw + 1);
	var->map.arraycpy[i] = malloc(sizeof(int) * var->map.maxw + 1);
	j = 0;
	k = 0;
	while (var->map.line[k])
	{
		while (var->map.line[k] == ' ')
			k++;
		if (!var->map.line[k])
			break ;
		else if (var->map.line[k] == 'N' || var->map.line[k] == 'E' ||
					var->map.line[k] == 'S' || var->map.line[k] == 'W')
			setplayer(&*var, i, j, k);
		else
		{
			var->map.maparray[i][j] = var->map.line[k] - '0';
			var->map.arraycpy[i][j] = var->map.line[k] - '0';
		}
		j++;
		k++;
	}
	linefinish(&*var, i, j);
}

void	gotomap(t_var *var)
{
	var->map.fd = open(var->map.file, O_RDONLY);
	get_next_line(var->map.fd, &(var->map.line));
	while (!ft_isdigit(var->map.line[0]))
	{
		free(var->map.line);
		get_next_line(var->map.fd, &(var->map.line));
	}
	var->player.pos.x = -1;
}

void	readmap(t_var *var)
{
	int	i;
	int	gnl;
	int check;

	i = 0;
	gnl = 1;
	check = 0;
	var->map.maparray = malloc(sizeof(int*) * var->map.h);
	var->map.arraycpy = malloc(sizeof(int*) * var->map.h);
	gotomap(&*var);
	while (ft_isdigit(var->map.line[0]))
	{
		createline(&*var, i);
		gnl = gnl == 1 ? get_next_line(var->map.fd, &(var->map.line)) : gnl;
		if (gnl != 1)
		{
			if (gnl == 0 && check == 1)
				break ;
			check = 1;
		}
		i++;
	}
	validmap(*var);
}
