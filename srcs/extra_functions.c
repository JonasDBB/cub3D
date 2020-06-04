/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:03:24 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/03 14:04:21 by jbennink      ########   odam.nl         */
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
