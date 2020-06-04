/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_set_values.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:51:57 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/03 15:24:39 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	i += digits(var->width);
	if (var->width > var->screenres.x && !var->save)
		var->width = var->screenres.x;
	while (var->map.line[i] == ' ')
		i++;
	if (var->map.line[i] == '\0' || var->width == 0)
		errormsg("error1 in res");
	var->height = ft_atoi(var->map.line + i);
	i += digits(var->height);
	if (var->height > var->screenres.y - 45 && !var->save)
		var->height = var->screenres.y - 45;
	while (var->map.line[i] == ' ')
		i++;
	if (var->map.line[i] != '\0' || var->height == 0)
		errormsg("error2 in res");
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
	if (line[i] != ',' || !ft_isdigit(line[i + 1]))
		errormsg("comma issue color");
	i++;
	g = ft_atoi(line + i);
	i += digits(g);
	if (line[i] != ',' || !ft_isdigit(line[i + 1]))
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
