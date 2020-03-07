/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:01 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/07 11:40:47 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE <= 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 255
# endif
# define END_OF_LINE '\n'
# define ERR -1
# define END 0
# define OK 1

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

int				get_next_line(int fd, char **line);
size_t			find_pos_eol(const char *line);
char			*ft_strjoin_special(char const *s1, char const *s2);

#endif
