/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 16:08:13 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/03 14:10:52 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H
# include "cub3d.h"

/*
**raycast.c, drawray.c, drawspprite.c, minimap.c, sprites.c
*/

void	pxdraw(t_data data, int x, int y, int color);
void	drawminimap(t_var *var, t_data *img);
void	drawimg(t_var *var, t_data *img);
void	drawray(t_var *var, t_data *img, t_cast caster, t_data texture);
void	drawminimap(t_var *var, t_data *img);
void	drawsprites(t_var *var, t_data *img, t_data texture);
void	createbmp(t_var var);
void	setup_sprites(t_var *var);
void	sortdist(t_var *var);

#endif
