/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:33:36 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 11:18:53 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"

void	floodfill(t_var *var, int x, int y);
void	validmap(t_var var);
void	errormsg(char *reason);
int		digits(unsigned long n);

void	setplayer(t_var *var, int i, int j, int k);
void	linefinish(t_var *var, int i, int j);
void	createline(t_var *var, int i);
void	gotomap(t_var *var);
void	readmap(t_var *var);

void	fillinput(t_var *var);
void	getlines(t_var *var);
void	getwidth(t_var *var);
void	checkend(t_var *var);
void	readinput(t_var *var);

void	setres(t_var *var);
void	settexture(char **dst, char *src, int i);
void	setcolor(char *line, int *clr, int i);
void	setdir(t_var *var);
void	setvector(t_coord *a, double i, double j);

// remove this
void	sysend(void);
#endif
