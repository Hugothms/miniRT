/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:30:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 14:44:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_atof(char *str)
{
	int		pos_point;
	int		decimal_size;
	float	nb;

	pos_point = 0;
	while (str[pos_point] && str[pos_point] != '.')
		pos_point++;
	decimal_size = 0;
	while (str[pos_point + 1 + decimal_size])
		decimal_size++;
	nb = (float)ft_atoi(&str[pos_point]) / (10 ^ decimal_size);
	nb += ft_atoi(str);
	return (nb);
}
