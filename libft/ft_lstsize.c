/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:43:29 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:39:45 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		i;

	i = 1;
	ptr = lst;
	if (!lst)
		return (0);
	while (ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
