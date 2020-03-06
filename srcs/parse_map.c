/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:25:15 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 16:17:37 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	setplayer(t_var *var, int i, int j, int k)
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

static void	linefinish(t_var *var, int i, int j)
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

static void	createline(t_var *var, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (var->map.line[k])
	{
		if (var->map.line[k] == ' ')
		{
			var->map.maparray[i][j] = -2;
			var->map.arraycpy[i][j] = -2;
		}
		else if (ft_strchr("NSEW", var->map.line[k]))
			setplayer(&*var, i, j, k);
		else if (var->map.line[k] > '2')
			errormsg("wrong shit in map");
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

static void	gotomap(t_var *var)
{
	var->map.maparray = malloc(sizeof(int*) * var->map.h);
	var->map.arraycpy = malloc(sizeof(int*) * var->map.h);
	var->map.fd = open(var->map.file, O_RDONLY);
	get_next_line(var->map.fd, &(var->map.line));
	while (!mapline(*var))
	{
		free(var->map.line);
		get_next_line(var->map.fd, &(var->map.line));
	}
	var->player.pos.x = -1;
}

void		readmap(t_var *var)
{
	int	i;
	int	gnl;
	int check;

	i = 0;
	gnl = 1;
	check = 0;
	gotomap(&*var);
	while (mapline(*var))
	{
		var->map.maparray[i] = malloc(sizeof(int) * var->map.maxw + 1);
		var->map.arraycpy[i] = malloc(sizeof(int) * var->map.maxw + 1);
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
