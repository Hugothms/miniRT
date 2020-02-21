# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 13:45:08 by hthomas           #+#    #+#              #
#    Updated: 2020/02/21 19:10:26 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang
CC = gcc
CFLAGS += -Wall -Werror -Wextra
LDFLAGS += -g3 -fsanitize=address

SRCS = 	srcs/color.c			\
		srcs/error.c			\
		srcs/get_next_line.c	\
		srcs/intersect_spheres.c\
		srcs/main.c				\
		srcs/make_img.c			\
		srcs/parse.c			\
		srcs/ray.c				\
		srcs/save_bmp.c			\
		srcs/set_elements.c		\
		srcs/set_elements2.c	\
		srcs/utils.c			\
		srcs/vector.c			\



OBJS = $(SRCS:.c=.o)
OBJSLIBFT =$(LIBFTDIR)*.o
NAME = miniRT

INCL = includes/
HEADER = $(INCL)minirt.h

LIBFT = libft.a
LIBFTDIR = libft/
LIBLINK = -L./libft -lft
MAKE = make

MLX_INCLUDE = -L./libmlx -lmlx -framework OpenGL -framework AppKit

OPTI = -Ofast #-O3





all : compilelibft $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OPTI) $(LDFLAGS) $(MLX_INCLUDE) -o $@ $(OBJSLIBFT) $^ $(LIBLINK)

compilelibft :
	$(MAKE) -C libft all

.c.o:
	$(CC) -c $(OPTI) $(LDFLAGS) -I$(INCL) -o $@ $<

clean:
	#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	cd $(LIBFTDIR) && $(MAKE) clean
	rm -rf $(OBJS) $(LIBFT)

fclean:		clean
	#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	cd $(LIBFTDIR) && $(MAKE) fclean
	rm -f $(NAME) a.out

re:		fclean all


.PHONY: clean fclean







###########################
--BLACK_FG =	\033[38;5;0m
RED_FG =	\033[38;5;196m
REDL_FG =	\033[1;31m
GREEN_FG =	\033[38;5;46m
CYAN_FG =	\033[0;36m
YELLOW_FG =	\033[1;33m

BLACK_BG =	\033[48;5;0m
BLUE_BG =	\033[48;5;39m
PINK_BG =	\033[48;5;213m
YELLOW_BG =	\033[48;5;11m
RANLIB_BG =	\033[48;5;172m
GREEN_BG =	\033[48;5;46m

CLEAR_COLOR =	\033[m
###########################


test: $(NAME)
	./$< example.rt

test_save: $(NAME)
	./$< example.rt -save



# gcc -g3 -fsanitize=address -lmlx -framework OpenGL -framework AppKit srcs/*.c -Iincludes libft/libft.a && ./a.out example.rt -save
#"sudo apt-get update" "sudo apt install gdb" "sudo apt install gcc"
#https://stackoverflow.com/c/42network/questions/950/954#954

