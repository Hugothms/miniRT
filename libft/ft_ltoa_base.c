/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:15:50 by hthomas           #+#    #+#             */
/*   Updated: 2019/12/12 17:58:07 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_len_nbr_l(unsigned long n, char *base_to)
{
	int		res;

	res = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		res++;
		n /= ft_strlen(base_to);
	}
	return (res);
}

char	*fill_positivenbr_base(unsigned long nbr, char *base, char *res, int i)
{
	int		size;

	size = 0;
	while (base[size])
		size++;
	if (nbr != 0)
	{
		res[i] = (base[nbr % size]);
		return (fill_positivenbr_base(nbr / size, base, res, i + 1));
	}
	return (res);
}

char	*fill_nbr_base(char *res, unsigned long nbr, char *base)
{
	int		i;
	int		size;

	size = 0;
	while (base[size])
		size++;
	i = 0;
	if (nbr != 0)
		res = fill_positivenbr_base(nbr, base, res, i);
	else if (nbr == 0)
		res[0] = (base[0]);
	return (res);
}

char	*ft_strrev_minus_1(char *res)
{
	int			i;
	char		c;
	int			len;

	i = 0;
	len = ft_strlen(res) - 1;
	while (i < len)
	{
		c = res[i];
		res[i++] = res[len];
		res[len--] = c;
	}
	return (res);
}

char	*ft_ltoa_base(unsigned long nb, char *base_to)
{
	char		*res;

	if (!check_base(base_to))
		return (0);
	if (!(res = malloc((ft_count_len_nbr_l(nb, base_to) + 1) * sizeof(char))))
		return (0);
	res[ft_count_len_nbr_l(nb, base_to)] = '\0';
	fill_nbr_base(res, nb, base_to);
	return (ft_strrev_minus_1(res));
}
