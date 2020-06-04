/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 15:50:26 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/03 14:05:04 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	dead(t_var *var)
{
	var->player.moved = 0;
	var->dead++;
	if (var->dead > 5)
	{
		sleep(2);
		mlx_destroy_window(var->mlx, var->win);
		exit(1);
	}
}

static int	renderframe(t_var *var)
{
	t_data	img;

	movement(&*var);
	if (var->dead > 0)
		dead(*&var);
	if (var->player.moved == 0)
		return (1);
	img.img = mlx_new_image(var->mlx, var->width, var->height);
	if (!img.img)
		errormsg("mlx image error");
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
									&img.line_length, &img.endian);
	drawimg(&*var, &img);
	sortdist(*&var);
	drawsprites(&*var, &img, var->tex.sp);
	drawminimap(&*var, &img);
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	if (var->player.hp <= 0)
		mlx_put_image_to_window(var->mlx, var->win,
						deathscreen(*&var).img, 0, 0);
	var->player.moved = 0;
	mlx_destroy_image(var->mlx, img.img);
	return (1);
}

static void	checkmap(char *s)
{
	int	fd;
	int	i;

	i = ft_strlen(s) - 1;
	if (s[i - 3] != '.' || s[i - 2] != 'c' || s[i - 1] != 'u' || s[i] != 'b')
		errormsg("inputfile not .cub");
	fd = open(s, O_RDONLY);
	if (fd == -1)
		errormsg("map doesn't exist");
	close(fd);
}

static void	setup(t_var *var, char *s)
{
	checkmap(s);
	var->map.file = s;
	var->sprites.count = 0;
	mlx_get_screen_size(var->mlx, &var->screenres.x, &var->screenres.y);
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
	if (!var->mlx)
		errormsg("mlx error");
	createtexture(&*var);
}

int			main(int ac, char **av)
{
	t_var	var;

	if (ac < 2 || ac > 3)
		errormsg("wrong number of arguments");
	var.save = 0;
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", 6))
			errormsg("wrong argument");
		var.save = 1;
	}
	setup(&var, av[1]);
	var.zbuffer = malloc(sizeof(double) * var.width);
	if (var.save)
	{
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
