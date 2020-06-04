/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:33:05 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/02 16:44:12 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		countsprites(int **arr, int h)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (i < h)
	{
		j = 0;
		while (arr[i][j] != -1)
		{
			if (arr[i][j] == 2)
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
}

static t_coord	*makespr(int **arr, int h, int size)
{
	int		i;
	int		j;
	int		k;
	t_coord	*res;

	i = 0;
	k = 0;
	res = malloc(sizeof(t_coord) * size);
	while (i < h)
	{
		j = 0;
		while (arr[i][j] != -1)
		{
			if (arr[i][j] == 2)
			{
				res[k].x = j + 0.5;
				res[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

static int		sortsprites(int *order, double *dist, int count)
{
	int	i;
	int	changed;

	i = 0;
	changed = 0;
	while (i < count - 1)
	{
		if (dist[i] > dist[i + 1])
		{
			dist[i] = dist[i] + dist[i + 1];
			dist[i + 1] = dist[i] - dist[i + 1];
			dist[i] = dist[i] - dist[i + 1];
			order[i] = order[i] + order[i + 1];
			order[i + 1] = order[i] - order[i + 1];
			order[i] = order[i] - order[i + 1];
			changed = 1;
		}
		i++;
	}
	return (changed);
}

void			sortdist(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->sprites.count)
	{
		var->sprites.order[i] = i;
		var->sprites.dist[i] = ((var->player.pos.x - var->sprites.locs[i].x) *
		(var->player.pos.x - var->sprites.locs[i].x) + (var->player.pos.y -
		var->sprites.locs[i].y) * (var->player.pos.y - var->sprites.locs[i].y));
		i++;
	}
	while (sortsprites(var->sprites.order, var->sprites.dist,
						var->sprites.count))
		;
}

void			setup_sprites(t_var *var)
{
	int	i;

	i = 0;
	var->sprites.count = countsprites(var->map.maparray, var->map.h);
	var->sprites.locs = makespr(var->map.maparray, var->map.h,
									var->sprites.count);
	var->sprites.order = malloc(sizeof(int*) * var->sprites.count);
	var->sprites.dist = malloc(sizeof(double*) * var->sprites.count);
}
