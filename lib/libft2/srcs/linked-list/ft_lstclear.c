/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:50:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/05 11:37:01 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Deletes and frees the given element and every successor of that element,
**  using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the
**  element.
*/

void	ft_lstclear(t_list **alst, void (*del)(void*))
{
	if (!*alst)
		return ;
	if ((*alst)->next)
	{
		ft_lstclear(&((*alst)->next), del);
		free((*alst)->next);
	}
	ft_lstdelone(*alst, del);
	*alst = NULL;
}
