/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:41:54 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 15:06:22 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		errormsg(char *reason)
{
	write(1, "Error\n", 6);
	ft_putstr_fd("reason: ", 1);
	ft_putstr_fd(reason, 1);
	write(1, "\n", 1);
	exit(0);
}
/*
**function to conveniently show leaks, called just before exit
**void		sysend(void)
**{
**	system("leaks a.out >> leaks.txt");
**	system("grep \"total leaked bytes\" leaks.txt");
**	system("rm leaks.txt");
**}
*/
