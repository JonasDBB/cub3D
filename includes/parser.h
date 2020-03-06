/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:33:36 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 15:04:51 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"

/*
**parse_input.c, parse_map.c, parse_utils.c, parse_set_values.c
*/

void	readinput(t_var *var);

void	readmap(t_var *var);

void	validmap(t_var var);
void	getwidth(t_var *var);
int		mapline(t_var var);
int		digits(unsigned long n);

void	setres(t_var *var);
void	settexture(char **dst, char *src, int i);
void	setcolor(char *line, int *clr, int i);
void	setdir(t_var *var);
void	setvector(t_coord *a, double i, double j);

#endif
