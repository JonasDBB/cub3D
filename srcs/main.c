/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 15:50:26 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 15:26:50 by jbennink      ########   odam.nl         */
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
			if (j == var.player.pos.x && i == var.player.pos.y)
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

void	printcpy(t_var var)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("floodfilled array\n");
	while (i < var.map.h)
	{
		j = 0;
		while (var.map.arraycpy[i][j] != -1)
		{
			if (j == var.player.pos.x && i == var.player.pos.y)
			{
				printf("\033[0;32m%c", var.map.direction);
				printf("\033[0m");
			}
			else if (var.map.arraycpy[i][j] == 9)
			{
				printf("\033[0;31m%c", 'X');
				printf("\033[0m");
			}
			else
				printf("%i", var.map.arraycpy[i][j]);
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

	movement(&*var);
	if (var->player.moved == 0)
		return (1);
	img.img = mlx_new_image(var->mlx, var->width, var->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
									&img.line_length, &img.endian);
	drawimg(&*var, &img);
	drawminimap(&*var, &img);
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	var->player.moved = 0;
	return (1);
}

unsigned int	lightendarken(int col, int n)
{
	return (((col & 0x0000FF) + n) | ((((col >> 8)
		& 0x00FF) + n) << 8) | (((col >> 16) + n) << 16));
}

void	texinc(char **texturepath, int i)
{
	(*texturepath) += i;
	while (**texturepath == ' ')
		(*texturepath)++;
}

void	texureincrease(t_var *var)
{
	texinc(&var->input.notexture, 2);
	texinc(&var->input.eatexture, 2);
	texinc(&var->input.sotexture, 2);
	texinc(&var->input.wetexture, 2);
	texinc(&var->input.spritetex, 1);
}

int		main(int ac, char **av)
{
	t_var	var;

	if (ac != 2)
		return (0);
	var.map.file = av[1];
	readinput(&var);
	readmap(&var);
	texureincrease(&var);
	var.player.pos.x += 0.5;
	var.player.pos.y += 0.5;
	var.player.spdmove = 0.05;
	var.player.spdrot = 0.025;
	var.player.moved = 1;
	var.mapscale = 30;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "map");
	mlx_hook(var.win, 2, 1L << 0, keyspress, &var);
	mlx_hook(var.win, 3, 2L << 0, keysrelease, &var);
	mlx_hook(var.win, 17, 0, key_escape, &var);
	mlx_loop_hook(var.mlx, renderframe, &var);
	mlx_loop(var.mlx);
	return (1);
}
