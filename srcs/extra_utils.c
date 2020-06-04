/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:41:54 by jbennink      #+#    #+#                 */
/*   Updated: 2020/06/02 15:16:58 by jbennink      ########   odam.nl         */
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

static void	texinc(char **texturepath, int i)
{
	(*texturepath) += i;
	while (**texturepath == ' ')
		(*texturepath)++;
}

void		preptextures(t_var *var)
{
	texinc(&var->input.notexture, 2);
	texinc(&var->input.eatexture, 2);
	texinc(&var->input.sotexture, 2);
	texinc(&var->input.wetexture, 2);
	texinc(&var->input.spritetex, 1);
}

void		checkpaths(t_input input)
{
	int	fd;

	fd = open(input.notexture, O_RDONLY);
	if (fd == -1)
		errormsg("north texture doesn't exist");
	close(fd);
	fd = open(input.eatexture, O_RDONLY);
	if (fd == -1)
		errormsg("east texture doesn't exist");
	close(fd);
	fd = open(input.sotexture, O_RDONLY);
	if (fd == -1)
		errormsg("south texture doesn't exist");
	close(fd);
	fd = open(input.wetexture, O_RDONLY);
	if (fd == -1)
		errormsg("west texture doesn't exist");
	close(fd);
	fd = open(input.spritetex, O_RDONLY);
	if (fd == -1)
		errormsg("sprite texture doesn't exist");
	close(fd);
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
