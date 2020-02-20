/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 16:08:13 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 14:13:53 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H
# include "cub3d.h"

void	pxdraw(t_data data, int x, int y, int color);
int		renderframe(t_var *var);

unsigned int	lightendarken(int col, int n);

void	drawminimap(t_var *var, t_data *img);

void	drawimg(t_var *var, t_data *img);
void	getdist(t_var *var, t_cast *caster, t_coord *side_d, t_coord delta_d);
int		findhit(t_var *var, t_cast *caster, t_coord *side_d, t_coord delta_d);
void	getheight(t_var *var, t_cast *caster);
void	drawray(t_var *var, t_data *img, t_cast caster);

void	drawminimap(t_var *var, t_data *img);

#endif
