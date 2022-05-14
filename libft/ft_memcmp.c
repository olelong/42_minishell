/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:47:31 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:12:03 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*temp1;
	const unsigned char	*temp2;

	i = 0;
	temp1 = (const unsigned char *)s1;
	temp2 = (const unsigned char *)s2;
	if (!n)
		return (0);
	while (i < n - 1 && temp1[i] == temp2[i])
		i++;
	return (temp1[i] - temp2[i]);
}
