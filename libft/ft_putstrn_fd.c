/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:16 by hthomas           #+#    #+#             */
/*   Updated: 2019/12/06 15:52:37 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrn_fd(const char *str, int fd, unsigned int n)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (n-- && str[i])
		ft_putchar_fd(str[i++], fd);
}
