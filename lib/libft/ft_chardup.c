/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chardup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:54 by hthomas           #+#    #+#             */
/*   Updated: 2019/12/12 11:10:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chardup(char c)
{
	char	*cpy;

	if (!(cpy = malloc((1 + 1) * sizeof(char))))
		return (NULL);
	cpy[0] = c;
	cpy[1] = '\0';
	return (cpy);
}
