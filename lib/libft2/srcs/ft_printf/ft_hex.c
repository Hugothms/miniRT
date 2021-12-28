/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:49:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:10:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_add_prefix(char *str, t_sp *sp, t_f *f, int uppercase)
{
	char	*tmp;
	char	*tmpstr;

	if (f->hash && sp->h)
	{
		tmp = str;
		if (!(tmpstr = ft_strdup(uppercase ? "0X" : "0x")))
			return (NULL);
		if (!(str = ft_strjoin(tmpstr, str)))
			return (NULL);
		free(tmp);
		free(tmpstr);
	}
	return (str);
}

char	*ft_precision_hex(char *str, t_sp *sp, t_f *f)
{
	if (f->precision)
	{
		if (!sp->h && !f->pr)
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

char	*ft_hex(va_list arg, t_sp *sp, t_f *f)
{
	char	*bl;
	char	*str;
	int		uppercase;

	bl = "0123456789abcdef";
	uppercase = f->plus;
	sp->h = va_arg(arg, unsigned int);
	if (!(str = ft_uitoa_base(sp->h, uppercase ? "0123456789ABCDEF" : bl)))
		return (NULL);
	if (!(str = ft_precision_hex(str, sp, f)))
		return (NULL);
	if (!(str = ft_add_prefix(str, sp, f, uppercase)))
		return (NULL);
	if (f->width)
	{
		if (!(str = ft_cat(f->minus, str, f->width,
		f->zero && !f->precision ? '0' : ' ')))
			return (NULL);
	}
	return (str);
}
