/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:18:37 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/11 00:20:47 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*elements;

	if (!lst || !f)
		return (NULL);
	elements = ft_lstnew(f(lst->content));
	if (elements == NULL)
		return (NULL);
	newlist = elements;
	lst = lst->next;
	while (lst)
	{
		elements = ft_lstnew(f(lst->content));
		if (!elements)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, elements);
		lst = lst->next;
	}
	return (newlist);
}
