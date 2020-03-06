/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 15:09:04 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 15:04:46 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "cub3d.h"

/*
**keys_main.c, keys_move.c, movement.c
*/

int		keyspress(int keycode, t_var *var);
int		key_escape(t_var *var);
void	key_right(t_var *var);
void	key_left(t_var *var);

void	key_a(t_var *var);
void	key_s(t_var *var);
void	key_d(t_var *var);
void	key_w(t_var *var);

int		keysrelease(int keycode, t_var *var);
void	movement(t_var *var);

#endif
