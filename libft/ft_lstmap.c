/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:55:26 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:34:41 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*ptr_new;

	new = malloc(sizeof(t_list));
	if (!lst || !new)
		return (NULL);
	while (lst)
	{
		ptr_new->content = (*f)(lst->content);
		if (lst->next)
		{
			ptr_new->next = malloc(sizeof(t_list));
			if (!ptr_new->next)
			{
				ft_lstclear(&new, (*del));
				return (NULL);
			}
			ptr_new = ptr_new->next;
		}
		lst = lst->next;
	}
	ptr_new->next = NULL;
	return (new);
}
