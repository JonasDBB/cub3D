/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsesetvalues5.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:51:57 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 15:01:33 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setres(t_var *var)
{
	int	i;

	i = 0;
	if (var->width != -1 || var->height != -1)
		errormsg("multiple inputs");
	i++;
	while (var->map.line[i] == ' ')
		i++;
	var->width = ft_atoi(var->map.line + i);
	if (var->width > 2560)
		var->width = 2560;
	while (var->map.line[i] != ' ')
		i++;
	while (var->map.line[i] == ' ')
		i++;
	var->height = ft_atoi(var->map.line + i);
	if (var->height > 1395)
		var->height = 1395;
}

void	settexture(char **dst, char *src, int i)
{
	if (*dst != NULL)
		errormsg("too many inputs texture");
	while (src[i] == ' ')
		i++;
	if (src[i] != '.')
		errormsg("wrong path for texture");
	while (src[i] == '.' || src[i] == '/')
	{
		if (src[i] == '/' && src[i - 1] != '.')
			errormsg("wrong path for texture");
		i++;
	}
	if (src[i - 1] != '/')
		errormsg("wrong path for texture");
	*dst = ft_strdup(src);
}

void	setcolor(char *line, int *clr, int i)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	while (line[i] == ' ')
		i++;
	r = ft_atoi(line + i);
	i += digits(r);
	if (line[i] != ',')
		errormsg("comma issue color");
	i++;
	g = ft_atoi(line + i);
	i += digits(g);
	if (line[i] != ',')
		errormsg("comma issue color");
	i++;
	b = ft_atoi(line + i);
	i += digits(b);
	while (line[i] == ' ')
		i++;
	if (line[i] || *clr != -1)
		errormsg("shit after color or more colors");
	if (r > 255 || g > 255 || b > 255)
		errormsg("wrong color numbers");
	*clr = r * 65536 + g * 256 + b;
}

void	setdir(t_var *var)
{
	if (var->map.direction == 'N')
	{
		setvector(&var->player.dir, 0, -1);
		setvector(&var->player.plane, 0.66, 0);
	}
	if (var->map.direction == 'E')
	{
		setvector(&var->player.dir, 1, 0);
		setvector(&var->player.plane, 0, 0.66);
	}
	if (var->map.direction == 'S')
	{
		setvector(&var->player.dir, 0, 1);
		setvector(&var->player.plane, -0.66, 0);
	}
	if (var->map.direction == 'W')
	{
		setvector(&var->player.dir, -1, 0);
		setvector(&var->player.plane, 0, -0.66);
	}
}

void	setvector(t_coord *a, double i, double j)
{
	a->x = i;
	a->y = j;
}
