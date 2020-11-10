# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 13:45:08 by hthomas           #+#    #+#              #
#    Updated: 2020/11/10 15:35:54 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= miniRT

HEAD	= includes

SRCDIR	= srcs/

LIB		= lib/

FILES	=	color.c					\
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


SRCS	= $(addprefix $(SRCDIR), $(FILES))
OBJS	= ${SRCS:.c=.o}
CC		= gcc -g
RM		= rm -f

CFLAGS	= -I $(HEAD) -D NUM_THREADS=$(NUM_THREADS)#-Wall -Wextra -Werror
FLAGS = -L $(LIB)libft -lft#-L $(LIB)libvector -lvct

MACOS_MACRO = -D MACOS
LINUX_MACRO = -D LINUX
MACOS_FLAGS	= -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
LINUX_FLAGS = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lpthread

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
endif

# ${NAME}:	${OBJS}
# 			make -C $(LIB)libft
# 			# make -C $(LIB)libvector
# 			${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}

$(NAME) : compilelibft compilelibmlx $(OBJS)
	${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}

compilelibft :
	make -C $(LIB)libft all

compilelibmlx :
	make -C $(LIB)minilibx-linux all

%.o: %.c $(HEAD)
	$(CC) -c -I$(HEAD) -o $@ $<

all:		${NAME}

clean:
			make clean -C $(LIB)libft
			# make clean -C $(LIB)libvector
			${RM} ${OBJS}

fclean:		clean
			make fclean -C $(LIB)libft
			# make fclean -C $(LIB)libvector
			${RM} ${NAME}

re:			fclean all








# NAME = miniRT
# --MAKE = make
# --CC = gcc
# --CFLAGS += -Wall -Werror -Wextra
# --LDFLAGS += #-g3 -fsanitize=address
# --OPTI = -Ofast -flto -march=native #-O3




# --OBJS = $(--SRCS:.c=.o)
# --OBJSLIBFT =$(--LIBFTDIR)*.o

# --INCL = includes/
# --HEADER = $(--INCL)minirt.h

# --LIBFT = libft.a
# --LIBFTDIR = libft/
# --LIBFTLINK = -L $(--LIBFTDIR)

# UNAME_S := $(shell uname -s)
# ifeq ($(UNAME_S), Linux)
# 	LIBMLXDIR	= libmlxlinux
# 	MLX_INCLUDE = -lm -lXext -lX11
# 	ENV			= -D LINUX
# else
# 	LIBMLXDIR	= libmlx
# 	MLX_INCLUDE = -framework OpenGL -framework AppKit
# 	ENV			=
# endif
# --LIBMLX = libmlx.a
# --LIBMLXLINK = -L $(LIBMLXDIR) -lmlx







# all : compilelibft compilelibmlx $(NAME)

# $(NAME) : $(--OBJSLIBFT) $(--OBJS)
# 	$(--CC) $(--OPTI) $(--LDFLAGS) -o $@ $^ $(--LIBFTLINK) $(--LIBMLXLINK) $(MLX_INCLUDE) $(ENV)

# compilelibft :
# 	$(--MAKE) -C libft all

# compilelibmlx :
# 	$(--MAKE) -C $(LIBMLXDIR) all

# %.o: %.c $(--INCL)
# 	$(--CC) -c $(--LDFLAGS) -I$(--INCL) -o $@ $<

# clean:
# 	#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
# 	cd $(--LIBFTDIR) && $(--MAKE) clean
# 	# cd $(LIBMLXDIR) && $(--MAKE) clean
# 	rm -rf $(--OBJS) $(--LIBFT) $(--LIBMLX)

# fclean:		clean
# 	#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
# 	cd $(--LIBFTDIR) && $(--MAKE) fclean
# 	# cd $(LIBMLXDIR) && $(--MAKE) fclean
# 	rm -f $(NAME) a.out

# re:		fclean all


# .PHONY: clean fclean




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


test: $(NAME)
	./$< scenes/test.rt

test_save: $(NAME)
	./$< scenes/test.rt -save



# gcc -g3 -fsanitize=address -lmlx -framework OpenGL -framework AppKit srcs/*.c -Iincludes libft/libft.a && ./a.out example.rt -save
#"sudo apt-get update" "sudo apt install gdb" "sudo apt install gcc"
#https://stackoverflow.com/c/42network/questions/950/954#954
#.SILENT:

