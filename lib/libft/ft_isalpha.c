/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:54 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/29 14:18:22 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isupper(int c)
{
	return (c <= 'Z' && c >= 'A');
}

int	ft_islower(int c)
{
	return (c <= 'z' && c >= 'a');
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
