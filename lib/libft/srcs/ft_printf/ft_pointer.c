/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:49:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:10:51 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_precision_pointer(char *str, t_sp *sp, t_f *f)
{
	if (f->precision)
	{
		if (!sp->p && !f->pr)
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
	}
	return (str);
}

char	*ft_pointer(va_list arg, t_sp *sp, t_f *f)
{
	char	*str;
	char	*tmp;
	char	*tmpstr;

	sp->p = va_arg(arg, unsigned long);
	if (!(str = ft_ltoa_base(sp->p, "0123456789abcdef")))
		return (NULL);
	if (!(str = ft_precision_pointer(str, sp, f)))
		return (NULL);
	tmp = str;
	if (!(tmpstr = ft_strdup("0x")))
		return (NULL);
	if (!(str = ft_strjoin(tmpstr, tmp)))
		return (NULL);
	free(tmp);
	free(tmpstr);
	if (f->width)
	{
		if (!(str = ft_cat(f->minus, str, f->width, f->zero ? '0' : ' ')))
			return (NULL);
	}
	return (str);
}
