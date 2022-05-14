/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:45:16 by afaure            #+#    #+#             */
/*   Updated: 2020/11/30 00:03:11 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *lst;
	while (ptr)
	{
		(*del)(ptr->content);
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	*lst = NULL;
}
