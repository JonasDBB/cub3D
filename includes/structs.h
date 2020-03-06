/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:42:55 by jbennink       #+#    #+#                */
/*   Updated: 2020/03/05 11:51:56 by jbennink      ########   odam.nl         */
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
	int		bpp;
	int		line_length;
	int		endian;
	int		texh;
	int		texw;
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
	int				x;
	int				side;
	int				drawstart;
	int				drawend;
	double			wall_d;
	t_intcrd		loc;
	t_intcrd		step;
	t_coord			raydir;
	int				lineh;
	unsigned int	clr;
	double			wallx;
	double			texstep;
	double			texpos;
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

typedef struct	s_textures {
	t_data	no;
	t_data	so;
	t_data	ea;
	t_data	we;
	t_data	sp;
}				t_textures;

typedef struct	s_sprites {
	t_coord	*locs;
	int		count;
	int		*order;
	double	*dist;
}				t_sprites;

typedef struct	s_sprvars {
	int			spr_screenx;
	int			spr_h;
	int			spr_w;
	int			line;
	double		invdet;
	t_coord		current;
	t_coord		transform;
	t_intcrd	drawstart;
	t_intcrd	drawend;
	t_intcrd	tex;
}				t_sprvars;

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
	t_textures	tex;
	t_sprites	sprites;
	double		*zbuffer;
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
