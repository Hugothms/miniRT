# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 13:45:08 by hthomas           #+#    #+#              #
#    Updated: 2020/01/09 11:21:20 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc
CC = clang
CFLAGS += -Wall -Werror -Wextra
LDFLAGS += -g3 -fsanitize=address

SRCS = 	srcs/main.c				\
		srcs/get_next_line.c

OBJS = $(SRCS:.c=.o)
OBJSLIBFT =$(LIBFTDIR)*.o
NAME = miniRT

INCL = includes/
HEADER = $(INCL)minirt.h

LIBFT = libft.a
LIBFTDIR = libft/
MAKE = make

EXEC = test.out
EXEC_HARDCORE = test_hardcore.out
EXEC_test = test_test.out
EXEC_precise = precise.out
LIBLINK = -L./ -lftprintf

MLX_INCLUDE = -lmlx -framework OpenGL -framework AppKit





###########################
BLACK_FG =	\033[38;5;0m
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


all : complib $(NAME)

$(OBJS) : %.o: %.c $(HEADER)
	@$(CC) -I $(INCL) -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) -o $@ $(MLX_INCLUDE) $(OBJS) $(OBJSLIBFT)

complib :
	@$(MAKE) -C libft all

clean:
	@#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	@cd $(LIBFTDIR) && $(MAKE) clean
	@rm -rf $(OBJS) $(LIBFT)

fclean:		clean
	@#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	@cd $(LIBFTDIR) && $(MAKE) fclean
	@rm -f $(NAME) $(EXEC) $(EXEC_HARDCORE) $(EXEC_test) $(EXEC_precise)

re:		fclean all

.c.o:
	@${CC} ${CFLAGS} -I$(INCLUDES) -c $< -o ${<:.c=.o}

.PHONY:	$(NAME) $(EXEC_precise)








test:	$(EXEC)
	./$<

$(EXEC):	$(NAME) main.c
	$(C) $(CFLAGS) -o $@ main.c -L./ -lftprintf

test_hardcore: $(EXEC_HARDCORE)
	./$<

$(EXEC_HARDCORE):	$(NAME) main_hardcore.c
	$(C) -o  $@ main_hardcore.c $(SRCS) -L./ -lftprintf


test_test: $(EXEC_test)
	./$<

$(EXEC_test): $(NAME) main_test.c
	$(C) $(LDFLAGS) -o $@ main_test.c -L./ -lftprintf

test_example:
	@./$(NAME) example.rt

$(EXEC_precise):	$(NAME) main_precise.c
	@#clear
	@$(C) $(CFLAGS) -o $@ main_precise.c $(LIBLINK)
