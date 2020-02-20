/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:42:55 by jbennink       #+#    #+#                */
/*   Updated: 2020/02/20 14:07:18 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_coord {
	double	x;
	double	y;
}				t_coord;

typedef struct	s_intcrd {
	int	x;
	int	y;
}				t_intcrd;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_player {
	t_coord	pos;
	t_coord	dir;
	t_coord	plane;
	double	spdmove;
	double	spdrot;
	int		moved;
}				t_player;

typedef struct	s_cast {
	int			x;
	int			side;
	int			drawstart;
	int			drawend;
	t_intcrd	loc;
	t_intcrd	step;
	t_coord		raydir;
}				t_cast;

typedef struct	s_map {
	char	*file;
	int		fd;
	char	*line;
	int		h;
	int		maxw;
	int		**maparray;
	int		**arraycpy;
	char	direction;
	int		valid;
}				t_map;

typedef struct	s_input {
	char	*notexture;
	char	*eatexture;
	char	*sotexture;
	char	*wetexture;
	char	*spritetex;
	int		clrfloor;
	int		clrceiling;
}				t_input;

typedef struct	s_var {
	void		*mlx;
	void		*win;
	t_map		map;
	t_input		input;
	int			width;
	int			height;
	t_player	player;
	int			mapscale;
	int			pressed[6];
}				t_var;

typedef struct	s_minimap {
	int	x;
	int	y;
	int	i;
	int	offset;
	int	sqwidth;
	int	maxsqw;
	int	maxsqh;
}				t_minimap;

#endif
