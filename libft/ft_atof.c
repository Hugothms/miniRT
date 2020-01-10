/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:30:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:25:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(const char *str)
{
	int		decimal_size;
	float	nb;
	int		sign;

	while (in_charset(*str, "\t "))
		str++;
	sign = 1;
	if (in_charset(*str, "-+"))
		sign *= (*str++ == '-' ? -1 : 1);
	nb = 0;
	nb += ft_atol(str);
	while (*str && in_charset(*str, "0123456789"))
		str++;
	if (*str == '.')
		str++;
	else
		return (nb);
	decimal_size = 0;
	while (in_charset(str[decimal_size], "0123456789"))
		decimal_size++;
	if (decimal_size)
		nb += ft_atol(str) / (ft_pow(10, decimal_size));
	else
		return (nb);
	return (nb * sign);
}
