/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:13:37 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:41:05 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*tempdst;
	const unsigned char	*tempsrc;

	tempdst = dst;
	tempsrc = src;
	i = 0;
	(void)c;
	while (i < n)
	{
		*(tempdst + i) = *(tempsrc + i);
		if (*(tempsrc + i) == (unsigned char)c)
			return (tempdst + i + 1);
		i++;
	}
	return (NULL);
}
