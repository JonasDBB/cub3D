/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:20:38 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/09 15:09:17 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../libft/libft.h"
# include "structs.h"
# include "parser.h"
# include "keys.h"
# include "drawing.h"

/*
**void	sysend(void);
*/
void		errormsg(char *reason);
void		preptextures(t_var *var);
void		checkpaths(t_input input);
t_data		deathscreen(t_var *var);

#endif
