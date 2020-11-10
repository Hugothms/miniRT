/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:49:16 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/02 16:06:53 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Counts the number of elements in a list
** @param lst	The beginning of the list
** @return		Length of the list
*/

int	ft_lstsize(t_list *lst)
{
	int		cpt;
	t_list	*pt;

	if (!lst)
		return (0);
	cpt = 1;
	pt = lst;
	while ((pt = pt->next))
		cpt++;
	return (cpt);
}
