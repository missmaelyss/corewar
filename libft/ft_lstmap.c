/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:19:57 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/22 13:23:41 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*tmp;

	if (lst)
	{
		tmp = f(lst);
		if (!(newlist = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		newlist = f(lst);
		newlist->next = ft_lstmap(lst->next, f);
		free(tmp);
		return (newlist);
	}
	return (NULL);
}
