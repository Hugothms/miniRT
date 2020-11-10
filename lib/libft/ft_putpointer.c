/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:00 by hthomas           #+#    #+#             */
/*   Updated: 2019/12/05 16:46:00 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putpointer(unsigned long long pointer)
{
	if (pointer < 16)
		ft_putchar(pointer + ((pointer < 10) ? '0' : 'a' - 10));
	else
	{
		ft_putpointer(pointer / 16);
		ft_putchar(pointer % 16 + (pointer % 16 < 10 ? '0' : 'a' - 10));
	}
}
