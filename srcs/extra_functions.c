/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:03:24 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/08 15:44:10 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	creatsingletexture(t_data *tex, char *input, void *mlx)
{
	tex->img = mlx_png_file_to_image(mlx,
			input, &tex->texw, &tex->texh);
	if (!tex->img)
		errormsg("texture is empty");
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_length, &tex->endian);
}

void		createtexture(t_var *var)
{
	preptextures(*&var);
	checkpaths(var->input);
	creatsingletexture(&var->tex.no, var->input.notexture, var->mlx);
	creatsingletexture(&var->tex.ea, var->input.eatexture, var->mlx);
	creatsingletexture(&var->tex.so, var->input.sotexture, var->mlx);
	creatsingletexture(&var->tex.we, var->input.wetexture, var->mlx);
	creatsingletexture(&var->tex.sp, var->input.spritetex, var->mlx);
}

void		checkset(t_var *var)
{
	var->check.north = 0;
	var->check.east = 0;
	var->check.south = 0;
	var->check.west = 0;
	var->check.sprite = 0;
	var->check.res = 0;
	var->check.floor = 0;
	var->check.ceiling = 0;
}

void		finishcheck(t_var *var)
{
	if (var->check.north == 0)
		errormsg("missing input for north texture");
	if (var->check.east == 0)
		errormsg("missing input for east texture");
	if (var->check.south == 0)
		errormsg("missing input for south texture");
	if (var->check.west == 0)
		errormsg("missing input for west texture");
	if (var->check.sprite == 0)
		errormsg("missing input for sprite texture");
	if (var->check.res == 0)
		errormsg("missing input for res");
	if (var->check.floor == 0)
		errormsg("missing input for floor colour");
	if (var->check.ceiling == 0)
		errormsg("missing input for ceiling colour");
}
