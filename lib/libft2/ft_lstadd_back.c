/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:49:44 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:52:47 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*pt;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	pt = *alst;
	while (pt->next)
		pt = pt->next;
	pt->next = new;
}
