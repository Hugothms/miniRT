/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:08:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_puthex(unsigned int hex, int upper)
{
	char	c;

	c = (upper ? 'A' : 'a');
	if (hex < 16)
		ft_putchar(hex + ((hex < 10) ? '0' : c - 10));
	else
	{
		ft_puthex(hex / 16, upper);
		ft_putchar(hex % 16 + (hex % 16 < 10 ? '0' : c - 10));
	}
}
