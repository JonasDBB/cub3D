/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 15:50:26 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/14 14:30:10 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printarray(t_var var)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < var.map.h)
	{
		j = 0;
		while (var.map.maparray[i][j] != -1)
		{
			if (j == var.map.playerx && i == var.map.playery)
			{
				printf("\033[0;32m%c", var.map.direction);
				printf("\033[0m");
			}
			else if (var.map.maparray[i][j] == 9)
			{
				printf("\033[0;31m%c", 'X');
				printf("\033[0m");
			}
			else
				printf("%i", var.map.maparray[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	pxdraw(t_data data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = (unsigned int)color;
}
int		renderframe(t_var *var)
{
	t_data	img;
	int		x = 0, y = 0, i = 0, j = 0;

	img.img = mlx_new_image(var->mlx, var->width, var->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//draw
	while (y < var->map.h * 64)
	{
		x = 0;
		j = 0;
		while (var->map.maparray[i][j] != -1)
		{
			if (var->map.maparray[i][j] == 0 || var->map.maparray[i][j] == 9)
				pxdraw(img, x, y, 0x00FFFFFF);
			if (i == var->map.playery && j == var->map.playerx)
				pxdraw(img, x, y, 0x00FF0000);
			if (var->map.maparray[i][j] == 1)
				pxdraw(img, x, y, 0x000000FF);
			if (var->map.maparray[i][j] == 2)
				pxdraw(img, x, y, 0x0000FF00);
			x++;
			j = x / 64;
		}
		y++;
		i = y / 64;
	}
	//end draw
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	return (1);
}

int		keys(int keycode, t_var *var)
{
	if (keycode == 53)
	{
		mlx_destroy_window(var->mlx, var->win);
		system("leaks a.out");
		exit(1);
	}
	return (1);
}

void	processrest(t_var *var)
{
	var->input.res++;
	while (*(var->input.res) == ' ')
		var->input.res++;
	var->width = ft_atoi(var->input.res);
	while (*(var->input.res) != ' ')
		var->input.res++;
	while (*(var->input.res) == ' ')
		var->input.res++;
	var->height = ft_atoi(var->input.res);
}

int		main(int argc, char **argv)
{
	t_var	var;

	var.map.file = argv[1];
	readinput(&var);
	readmap(&var);
	printarray(var);
	processrest(&var);
	printf("DONE\n");
	sysend();
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "map");
	mlx_hook(var.win, 2, 1L << 0, keys, &var);
	mlx_loop_hook(var.mlx, renderframe, &var);
	mlx_loop(var.mlx);
	return (1);
}
