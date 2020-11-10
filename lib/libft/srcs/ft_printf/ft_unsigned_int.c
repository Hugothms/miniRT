/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:49:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:10:51 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*precision_unsigned(char *str, t_sp *sp, t_f *f)
{
	if (!sp->u && !f->pr)
	{
		free(str);
		if (!(str = ft_chardup('\0')))
			return (NULL);
	}
	else
	{
		if (!(str = ft_cat(0, str, f->pr, '0')))
			return (NULL);
	}
	return (str);
}

char	*ft_unsigned_int(va_list arg, t_sp *sp, t_f *f)
{
	char	*str;

	sp->u = va_arg(arg, unsigned int);
	if (!(str = ft_uitoa(sp->u)))
		return (NULL);
	if (f->precision)
	{
		if (!(str = precision_unsigned(str, sp, f)))
			return (NULL);
	}
	if (f->width)
	{
		if (!(str = ft_cat(f->minus, str, f->width,
		f->zero && !f->precision ? '0' : ' ')))
			return (NULL);
	}
	return (str);
}
