/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 13:12:56 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/10 15:34:54 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*recurs(int depth, int *ret, int fd)
{
	char	buff[1];
	char	*line;
	int		test;

	test = read(fd, buff, 1);
	if (test == 0)
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0)
	{
		line = malloc(sizeof(char) * depth + 1);
		line[depth] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (line);
	}
	else
	{
		line = recurs(depth + 1, ret, fd);
		line[depth] = buff[0];
	}
	return (line);
}

int		get_next_line( int fd, char **line)
{
	int ret;

	ret = 1;
	*line = recurs(0, &ret, fd);
	return (ret);
}
