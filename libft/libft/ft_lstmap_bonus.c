/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:33:30 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/08 09:15:30 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*addtomap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*newcont;
	t_list	*newnode;

	newcont = f(lst->content);
	newnode = ft_lstnew(newcont);
	if (!newnode)
	{
		del(newcont);
		return (NULL);
	}
	return (newnode);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newstart;

	if (!lst || !f || !del)
		return (NULL);
	newstart = addtomap(lst, f, del);
	if (!newstart)
		return (NULL);
	newlst = newstart;
	lst = lst->next;
	while (lst)
	{
		newlst->next = addtomap(lst, f, del);
		if (!newlst->next)
		{
			ft_lstclear(&newstart, del);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	newlst->next = NULL;
	return (newstart);
}
