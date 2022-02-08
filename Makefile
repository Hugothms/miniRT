# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 13:45:08 by hthomas           #+#    #+#              #
#    Updated: 2022/02/08 11:09:24 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= miniRT

INCLDIR	= includes/

SRCDIR	= srcs/

LIB		= lib/

SRCFILES=	color.c					\
			error.c					\
			intersect_cylinders.c	\
			intersect_planes.c		\
			intersect_spheres.c		\
			intersect_squares.c		\
			intersect_triangles.c	\
			main.c					\
			make_img.c				\
			parse.c					\
			ray.c					\
			save_bmp.c				\
			set_elements.c			\
			set_elements2.c			\
			utils.c					\
			vector.c				\


INCLFILES=	basics.h				\
			elements.h minirt.h		\
			mlx.h					\
			parse.h					\
			scene.h					\

SRCS	= $(addprefix $(SRCDIR), $(SRCFILES))
OBJS	= $(SRCS:.c=.o)
INCLS	= $(addprefix $(INCLDIR), $(INCLFILES))
CC		= gcc -g
RM		= rm -f

CFLAGS	= -I $(INCLDIR) -DTHREADS=$(THREADS) -Wall -Wextra -fsanitize=address -g3#-Werror -Ofast
FLAGS = -L $(LIB)libft -lft -L $(LIB)libmlx -lmlx

MACOS_MACRO = -DMACOS
LINUX_MACRO = -DLINUX
MACOS_FLAGS	= -framework OpenGL -framework AppKit
LINUX_FLAGS = -lm -lX11 -lXext -lpthread

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
endif

$(NAME) : compilelibft compilelibmlx $(OBJS) $(INCLS)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

compilelibft :
	make -C $(LIB)libft all

compilelibmlx :
	make -C $(LIB)libmlx all

%.o: %.c $(INCLS)
	$(CC) $(CFLAGS) -c -I $(INCLDIR) -o $@ $<

all:		$(NAME)

clean:
			make clean -C $(LIB)libft
			# make clean -C $(LIB)libvector
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C $(LIB)libft
			# make fclean -C $(LIB)libvector
			$(RM) $(NAME)

re:			fclean all

run: $(NAME)
	./$< scenes/test.rt

run_scene: $(NAME)
	./$< scenes/$(filter-out $@, $(MAKECMDGOALS)).rt

run_save: $(NAME)
	./$< scenes/test.rt -save

run_all: $(NAME)
	./$< scenes/90spheres.rt &
	./$< scenes/circle.rt &
	./$< scenes/cylinder.rt &
	./$< scenes/default.rt &
	./$< scenes/example.rt &
	./$< scenes/gradient.rt &
	./$< scenes/mollecules.rt &
	./$< scenes/peach.rt &
	./$< scenes/square.rt &
	./$< scenes/triangle.rt &
	./$< scenes/test.rt

# ###########################
# --BLACK_FG =	\033[38;5;0m
# --RED_FG =	\033[38;5;196m
# --REDL_FG =	\033[1;31m
# --GREEN_FG =	\033[38;5;46m
# --CYAN_FG =	\033[0;36m
# --YELLOW_FG =	\033[1;33m

# --BLACK_BG =	\033[48;5;0m
# --BLUE_BG =	\033[48;5;39m
# --PINK_BG =	\033[48;5;213m
# --YELLOW_BG =	\033[48;5;11m
# --RANLIB_BG =	\033[48;5;172m
# --GREEN_BG =	\033[48;5;46m

# --CLEAR_COLOR =	\033[m
# ###########################
