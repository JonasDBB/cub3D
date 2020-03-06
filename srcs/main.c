/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 15:50:26 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 19:17:21 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	deathscreen(t_var *var)
{
	t_data	img;
	int		x;
	int		y;

	img.img = mlx_new_image(var->mlx, var->width, var->height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
									&img.line_length, &img.endian);
	y = 0;
	while (y < var->height)
	{
		x = 0;
		while (x < var->width)
		{
			pxdraw(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	mlx_string_put(var->mlx, var->win, var->width * 0.5,
					var->height * 0.5, 0xFF0000, "YOU DIED");
}

static int	renderframe(t_var *var)
{
	t_data	img;

	movement(&*var);
	if (var->dead == 1)
	{
		sleep(2);
		exit(1);
	}
	if (var->player.moved == 0)
		return (1);
	img.img = mlx_new_image(var->mlx, var->width, var->height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
									&img.line_length, &img.endian);
	drawimg(&*var, &img);
	sortdist(*&var);
	drawsprites(&*var, &img, var->tex.sp);
	drawminimap(&*var, &img);
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	if (var->player.hp <= 0)
	{
		deathscreen(*&var);
		var->dead = 1;
	}
	var->player.moved = 0;
	return (1);
}

static void	createtexture(t_var *var)
{
	preptextures(*&var);
	checkpaths(var->input);
	var->tex.no.img = mlx_png_file_to_image(var->mlx,
			var->input.notexture, &var->tex.no.texw, &var->tex.no.texh);
	var->tex.no.addr = mlx_get_data_addr(var->tex.no.img,
			&var->tex.no.bpp, &var->tex.no.line_length, &var->tex.no.endian);
	var->tex.ea.img = mlx_png_file_to_image(var->mlx,
			var->input.eatexture, &var->tex.ea.texw, &var->tex.ea.texh);
	var->tex.ea.addr = mlx_get_data_addr(var->tex.ea.img,
			&var->tex.ea.bpp, &var->tex.ea.line_length, &var->tex.ea.endian);
	var->tex.so.img = mlx_png_file_to_image(var->mlx,
			var->input.sotexture, &var->tex.so.texw, &var->tex.so.texh);
	var->tex.so.addr = mlx_get_data_addr(var->tex.so.img,
			&var->tex.so.bpp, &var->tex.so.line_length, &var->tex.so.endian);
	var->tex.we.img = mlx_png_file_to_image(var->mlx,
			var->input.wetexture, &var->tex.we.texw, &var->tex.we.texh);
	var->tex.we.addr = mlx_get_data_addr(var->tex.we.img,
			&var->tex.we.bpp, &var->tex.we.line_length, &var->tex.we.endian);
	var->tex.sp.img = mlx_png_file_to_image(var->mlx,
			var->input.spritetex, &var->tex.sp.texw, &var->tex.sp.texh);
	var->tex.sp.addr = mlx_get_data_addr(var->tex.sp.img,
			&var->tex.sp.bpp, &var->tex.sp.line_length, &var->tex.sp.endian);
}

static void	setup(t_var *var, char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (s[i - 3] != '.' || s[i - 2] != 'c' || s[i - 1] != 'u' || s[i] != 'b')
		errormsg("inputfile not .cub");
	var->map.file = s;
	var->sprites.count = 0;
	readinput(&*var);
	readmap(&*var);
	var->player.pos.x += 0.5;
	var->player.pos.y += 0.5;
	var->basespeed = 1;
	var->sprint = 3;
	var->player.spdmove = var->basespeed * 0.05;
	var->player.spdrot = var->basespeed * 0.02;
	var->player.moved = 1;
	var->mapscale = 28;
	var->player.hp = 100;
	var->dead = 0;
	setup_sprites(&*var);
	var->mlx = mlx_init();
	createtexture(&*var);
}

int			main(int ac, char **av)
{
	t_var	var;

	if (ac < 2 || ac > 3)
		errormsg("wrong number of arguments");
	setup(&var, av[1]);
	var.zbuffer = malloc(sizeof(double) * var.width);
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", 6))
			errormsg("wrong argument");
		createbmp(var);
		return (1);
	}
	var.win = mlx_new_window(var.mlx, var.width, var.height, "map");
	mlx_hook(var.win, 2, 1L << 0, keyspress, &var);
	mlx_hook(var.win, 3, 2L << 0, keysrelease, &var);
	mlx_hook(var.win, 17, 0, key_escape, &var);
	mlx_loop_hook(var.mlx, renderframe, &var);
	mlx_loop(var.mlx);
	return (1);
}
