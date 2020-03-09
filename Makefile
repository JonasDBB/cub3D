# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbennink <jbennink@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/06 15:08:36 by jbennink       #+#    #+#                 #
#    Updated: 2020/03/09 15:36:21 by jbennink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

MINILIB = libmlx.dylib

FLAGS = -Wall -Wextra -Werror -O3

INCLUDES = includes/

_SRCS = bitmap.c \
draw_ray.c \
draw_sprite.c \
extra_utils.c \
keys_main.c \
keys_move.c \
main.c \
minimap.c \
movement.c \
parse_input.c \
parse_map.c \
parse_set_values.c \
parse_utils.c \
raycast.c \
sprites.c

SRCS = $(addprefix srcs/, $(_SRCS))

OBJS = $(addprefix objects/, $(_SRCS:.c=.o))

.PHONY: all clean fclean re libs

all: $(NAME)

objects/%.o: srcs/%.c
	@mkdir -p objects
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(MINILIB) $(LIBFT) $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIB)

clean:
	rm -f $(OBJS)
	rm -r objects/
	cd libft && $(MAKE) clean
	cd minilibx_mms_20200219 && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MINILIB)
	cd libft && $(MAKE) fclean

re: fclean all

bonus: all

$(LIBFT):
	cd libft && $(MAKE) all

$(MINILIB):
	cd minilibx_mms_20200219 && $(MAKE)
	cp minilibx_mms_20200219/$(MINILIB) .
