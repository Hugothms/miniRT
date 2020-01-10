# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:49:24 by hthomas           #+#    #+#              #
#    Updated: 2020/01/10 17:28:29 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a
OBJS		=	${SRCS:.c=.o}
INCLUDES	=	libft.h
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
SRCS 		=	ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memccpy.c			\
				ft_memmove.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_strlen.c				\
				ft_isalpha.c			\
				ft_isdigit.c			\
				ft_issign.c				\
				ft_isalnum.c			\
				ft_isascii.c			\
				ft_isprint.c			\
				ft_toupper.c			\
				ft_tolower.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strncmp.c			\
				ft_strnstr.c			\
				ft_strlcpy.c			\
				ft_strlcat.c			\
				ft_atoi.c				\
				ft_atoi_base.c			\
				ft_atol.c				\
				ft_atof.c				\
				ft_itoa.c				\
				ft_uitoa.c				\
				ft_ltoa.c				\
				ft_ltoa_base.c			\
				ft_uitoa_base.c			\
				ft_putnbr_base.c		\
				ft_convert_base.c		\
				ft_calloc.c				\
				ft_chardup.c			\
				ft_strdup.c				\
				ft_substr.c				\
				ft_putnbr_fd.c			\
				ft_putnbr.c				\
				ft_putnbr_unsigned_fd.c	\
				ft_putnbr_unsigned.c	\
				ft_puthex.c				\
				ft_putpointer.c			\
				ft_count_len_hex.c		\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_strmapi.c			\
				ft_split.c				\
				ft_strtrim.c			\
				ft_strjoin.c			\
				ft_lstnew.c				\
				ft_lstadd_front.c		\
				ft_lstsize.c			\
				ft_lstlast.c			\
				ft_lstadd_back.c		\
				ft_lstdelone.c			\
				ft_lstclear.c			\
				ft_lstiter.c			\
				ft_lstmap.c				\
				ft_putchar.c			\
				ft_putstr.c				\
				ft_putstrn.c			\
				ft_putstrn_fd.c			\
				ft_putnbr_base.c		\
				ft_strcmp.c				\
				ft_strstr.c				\
				ft_strcat.c				\
				ft_strmap.c				\
				ft_split_set.c			\
				ft_strjoin_sep.c		\
				ft_is_from_charset.c	\
				ft_pow.c


###########################
BLACK_FG = \033[38;5;0m
RED_FG = \033[38;5;196m
GREEN_FG = \033[38;5;46m

BLACK_BG = \033[48;5;0m
BLUE_BG = \033[48;5;39m
PINK_BG = \033[48;5;213m
YELLOW_BG = \033[48;5;11m
RANLIB_BG = \033[48;5;172m

CLEAR_COLOR = \033[m
###########################



all:		$(NAME)

$(NAME):	${OBJS}
	@echo "Creating $(GREEN_FG)libft.a $(CLEAR_COLOR)"
	@ar rc	$(NAME) ${OBJS}
	@ranlib	$(NAME)

.c.o:
	@${CC} ${CFLAGS} -I$(INCLUDES) -c $< -o ${<:.c=.o}

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all
