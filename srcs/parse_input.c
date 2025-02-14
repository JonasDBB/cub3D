/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:23:43 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/08 15:43:16 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fillinput(t_var *var)
{
	if (var->map.line[0] == 'R')
		setres(&*var);
	else if (var->map.line[0] == 'N' && var->map.line[1] == 'O')
		settexture(&var->input.notexture, var->map.line, 2, &var->check.north);
	else if (var->map.line[0] == 'E' && var->map.line[1] == 'A')
		settexture(&var->input.eatexture, var->map.line, 2, &var->check.east);
	else if (var->map.line[0] == 'S' && var->map.line[1] == 'O')
		settexture(&var->input.sotexture, var->map.line, 2, &var->check.south);
	else if (var->map.line[0] == 'W' && var->map.line[1] == 'E')
		settexture(&var->input.wetexture, var->map.line, 2, &var->check.west);
	else if (var->map.line[0] == 'S')
		settexture(&var->input.spritetex, var->map.line, 1, &var->check.sprite);
	else if (var->map.line[0] == 'F')
	{
		var->check.floor = 1;
		setcolor(var->map.line, &var->input.clrfloor, 1);
	}
	else if (var->map.line[0] == 'C')
	{
		var->check.ceiling = 1;
		setcolor(var->map.line, &var->input.clrceiling, 1);
	}
	else
		errormsg("unknown input");
}

static int	mapstart(t_var *var)
{
	int	i;

	i = 0;
	while (var->map.line[i] == ' ')
		i++;
	if (var->map.line[i] >= '0' && var->map.line[i] <= '2')
	{
		getwidth(*&var);
		return (1);
	}
	return (0);
}

static void	getlines(t_var *var)
{
	var->input.notexture = NULL;
	var->input.eatexture = NULL;
	var->input.sotexture = NULL;
	var->input.wetexture = NULL;
	var->input.spritetex = NULL;
	var->input.clrceiling = -1;
	var->input.clrfloor = -1;
	var->height = -1;
	var->width = -1;
	var->map.h = 0;
	while (get_next_line(var->map.fd, &(var->map.line)) == 1)
	{
		if (mapstart(*&var))
			return ;
		while (var->map.line[0] == '\0')
		{
			free(var->map.line);
			get_next_line(var->map.fd, &(var->map.line));
		}
		if (mapstart(*&var))
			return ;
		fillinput(&*var);
		free(var->map.line);
	}
	free(var->map.line);
}

static void	checkend(t_var *var)
{
	int	gnl;
	int	i;

	if (var->map.line[0] != '\0')
		errormsg("stuff after map");
	gnl = get_next_line(var->map.fd, &(var->map.line));
	while ((var->map.line[0] == '\0' || var->map.line[0] == ' ') && gnl == 1)
	{
		i = 0;
		while (var->map.line[i] == ' ')
			i++;
		if (var->map.line[i] != '\0')
			errormsg("stuff after map");
		free(var->map.line);
		gnl = get_next_line(var->map.fd, &(var->map.line));
	}
	if (var->map.line[0] != '\0')
		errormsg("stuff after map");
	free(var->map.line);
}

void		readinput(t_var *var)
{
	int	gnl;
	int	i;

	gnl = 1;
	var->map.fd = open(var->map.file, O_RDONLY);
	var->map.maxw = 0;
	getlines(&*var);
	while (gnl > -1)
	{
		gnl = get_next_line(var->map.fd, &(var->map.line));
		i = 0;
		while (var->map.line[i] == ' ')
			i++;
		if (var->map.line[i] <= '0' || var->map.line[i] >= '2' || gnl == 0)
		{
			if (var->map.line[i] != '\0')
				var->map.h++;
			free(var->map.line);
			break ;
		}
		getwidth(&*var);
	}
	if (gnl)
		checkend(&*var);
	close(var->map.fd);
}
