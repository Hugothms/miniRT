/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 10:30:17 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 10:31:34 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	find_pos_eol(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	return (i);
}

char	*ft_strjoin_special(char const *s1, char const *s2)
{
	char	*new;
	size_t	lens1;
	size_t	lens2;
	int		i;

	i = 0;
	lens1 = (!s1) ? 0 : ft_strlen(s1);
	lens2 = find_pos_eol(&s2[i]);
	if (!(new = malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	ft_memmove(new, s1, lens1);
	ft_memmove(new + lens1, &s2[i], lens2);
	new[lens1 + lens2] = '\0';
	return (new);
}

int		fill_line_with_buff(char **line, char buff[][BUFFER_SIZE + 2], int fd)
{
	size_t		len;
	size_t		eol;
	char		*tmp;

	if (!*buff[fd] && **line)
		return (OK);
	if (*buff[fd] == END_OF_LINE && !buff[fd][1])
	{
		ft_memmove(buff[fd], &buff[fd][1], 1);
		return (OK);
	}
	eol = find_pos_eol(buff[fd]);
	len = ft_strlen(&buff[fd][eol]);
	tmp = *line;
	*line = ft_strjoin_special(tmp, &buff[fd][0]);
	free(tmp);
	ft_memmove(buff[fd], &buff[fd][eol] + 1, len + 1);
	buff[fd][len] = '\0';
	if (len != BUFFER_SIZE)
		ft_bzero(&buff[fd][len], eol);
	if (len)
		return (OK);
	return (END);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX + 1][BUFFER_SIZE + 2];
	size_t		bytes_read;

	if (BUFFER_SIZE == 0 || fd < 0 || fd > OPEN_MAX + 1 || !line)
		return (ERR);
	if (!(*line = malloc(sizeof(char))))
		return (ERR);
	**line = 0;
	while (*buff[fd])
	{
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	while ((bytes_read = read(fd, buff[fd], BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (ERR);
		buff[fd][bytes_read] = '\0';
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	return (END);
}
