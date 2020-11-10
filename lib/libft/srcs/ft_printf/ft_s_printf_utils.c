/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_printf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:25:55 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:09:52 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_sp	*init_sp(void)
{
	t_sp	*sp;

	if (!(sp = (t_sp*)malloc(sizeof(t_sp))))
		return (NULL);
	ft_bzero(sp, sizeof(*sp));
	return (sp);
}

t_sp	*reset_sp(t_sp *sp)
{
	sp->i = 0;
	sp->u = 0;
	sp->s = NULL;
	sp->p = 0;
	sp->h = 0;
	return (sp);
}

void	free_sp(t_sp *sp)
{
	free(sp);
}

t_f		*init_f(void)
{
	t_f	*f;

	if (!(f = (t_f*)malloc(sizeof(t_f))))
		return (NULL);
	f->zero = 0;
	f->minus = 0;
	f->width = 0;
	f->precision = 0;
	f->pr = 0;
	f->space = 0;
	f->hash = 0;
	f->plus = 0;
	return (f);
}
