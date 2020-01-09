/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_len_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:53:02 by hthomas           #+#    #+#             */
/*   Updated: 2019/12/05 16:43:54 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_count_len_hex(unsigned long long hex)
{
	int	res;

	res = 0;
	if (hex == 0)
		return (1);
	while (hex)
	{
		res++;
		hex /= 16;
	}
	return (res);
}
