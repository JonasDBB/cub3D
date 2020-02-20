/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parseinput.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:23:43 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/19 13:28:21 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fillinput(t_var *var)
{
	if (var->map.line[0] == 'R')
		setres(&*var);
	else if (var->map.line[0] == 'N' && var->map.line[1] == 'O')
		settexture(&var->input.notexture, var->map.line, 2);
	else if (var->map.line[0] == 'E' && var->map.line[1] == 'A')
		settexture(&var->input.eatexture, var->map.line, 2);
	else if (var->map.line[0] == 'S' && var->map.line[1] == 'O')
		settexture(&var->input.sotexture, var->map.line, 2);
	else if (var->map.line[0] == 'W' && var->map.line[1] == 'E')
		settexture(&var->input.wetexture, var->map.line, 2);
	else if (var->map.line[0] == 'S')
		settexture(&var->input.spritetex, var->map.line, 1);
	else if (var->map.line[0] == 'F')
		setcolor(var->map.line, &var->input.clrfloor, 1);
	else if (var->map.line[0] == 'C')
		setcolor(var->map.line, &var->input.clrceiling, 1);
	else
		errormsg("unknown input");
}

void	getlines(t_var *var)
{
	var->input.notexture = NULL;
	var->input.eatexture = NULL;
	var->input.sotexture = NULL;
	var->input.wetexture = NULL;
	var->input.spritetex = NULL;
	var->input.clrceiling = -1;
	var->input.clrfloor = -1;
	while (get_next_line(var->map.fd, &(var->map.line)) == 1
			&& var->map.line[0] != '1')
	{
		while (var->map.line[0] == '\0')
		{
			free(var->map.line);
			get_next_line(var->map.fd, &(var->map.line));
		}
		if (var->map.line[0] >= '0' && var->map.line[0] <= '2')
		{
			getwidth(*&var);
			return ;
		}
		fillinput(&*var);
		free(var->map.line);
	}
	free(var->map.line);
}

void	getwidth(t_var *var)
{
	int	maxw;
	int	i;

	maxw = 0;
	i = 0;
	while (var->map.line[i])
	{
		if (var->map.line[i] != ' ')
			maxw++;
		i++;
	}
	if (maxw > var->map.maxw)
		var->map.maxw = maxw;
	var->map.h++;
	free(var->map.line);
}

void	checkend(t_var *var)
{
	int	gnl;
	int	i;

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

void	readinput(t_var *var)
{
	int	gnl;

	gnl = 1;
	var->map.fd = open(var->map.file, O_RDONLY);
	var->height = -1;
	var->width = -1;
	var->map.h = 0;
	var->map.maxw = 0;
	getlines(&*var);
	while (gnl > -1)
	{
		gnl = get_next_line(var->map.fd, &(var->map.line));
		if (var->map.line[0] == '\0' || gnl == 0)
		{
			if (var->map.line[0] != '\0')
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
