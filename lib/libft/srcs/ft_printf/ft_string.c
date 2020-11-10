/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:49:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:10:51 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_precision_string(char *str, t_sp *sp, t_f *f)
{
	if (f->precision)
	{
		if (!sp->s && !f->pr)
		{
			free(str);
			if (!(str = ft_chardup('\0')))
				return (NULL);
		}
		else
		{
			if (f->precision && (int)ft_strlen(str) > f->pr)
				str[f->pr] = '\0';
		}
	}
	return (str);
}

char	*ft_string(va_list arg, t_sp *sp, t_f *f)
{
	char	*str;

	sp->s = va_arg(arg, char*);
	if (!sp->s)
	{
		if (!(str = ft_strdup("(null)")))
			return (NULL);
	}
	else
	{
		if (!(str = ft_strdup(sp->s)))
			return (NULL);
	}
	if (!(str = ft_precision_string(str, sp, f)))
		return (NULL);
	if (f->width)
	{
		if (!(str = ft_cat(f->minus, str, f->width,
		f->zero && !f->minus ? '0' : ' ')))
			return (NULL);
	}
	return (str);
}
