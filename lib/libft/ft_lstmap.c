/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:51:17 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/20 16:37:20 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*mapedlst;

	if (!lst || !f || !del)
		return (NULL);
	tmp = lst;
	if (!(mapedlst = ft_lstnew(f(tmp->content))))
		ft_lstclear(&mapedlst, del);
	tmp = tmp->next;
	while (tmp)
	{
		if (!(new = ft_lstnew(f(tmp->content))))
			ft_lstclear(&mapedlst, del);
		ft_lstadd_back(&mapedlst, new);
		tmp = tmp->next;
	}
	return (mapedlst);
}
