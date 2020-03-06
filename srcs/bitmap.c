/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 13:43:19 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/06 16:12:58 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	writeheader(t_var var, int fd)
{
	char	s[54];
	int		wid;
	int		padding;

	ft_bzero(s, 54);
	s[0] = 0x42;
	s[1] = 0x4D;
	wid = var.width;
	padding = 0;
	while ((3 * wid + padding) % 4 != 0)
		padding++;
	s[2] = 3 * (wid + padding) * var.height + 54;
	s[10] = 54;
	s[14] = 40;
	ft_memcpy(s + 18, &var.width, 4);
	ft_memcpy(s + 22, &var.height, 4);
	s[26] = 1;
	s[28] = 24;
	write(fd, s, 54);
	return (padding);
}

static void	createimg(t_var var, t_data *img)
{
	img->img = mlx_new_image(var.mlx, var.width, var.height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
									&img->line_length, &img->endian);
	drawimg(&var, &*img);
	sortdist(&var);
	drawsprites(&var, &*img, var.tex.sp);
	drawminimap(&var, &*img);
}

void		createbmp(t_var var)
{
	int			fd;
	t_data		img;
	t_intcrd	c;
	char		*clr;
	int			padding;

	createimg(var, &img);
	fd = open("screen.bmp", O_RDWR | O_CREAT, 0666);
	padding = writeheader(var, fd);
	c.y = var.height - 1;
	while (c.y >= 0)
	{
		c.x = 0;
		while (c.x < var.width)
		{
			clr = (img.addr + (c.y * img.line_length + c.x * (img.bpp / 8)));
			write(fd, clr, 3);
			c.x++;
		}
		write(fd, "\0\0\0", padding);
		c.y--;
	}
	close(fd);
}
