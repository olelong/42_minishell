/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 00:20:20 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:08:20 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_topdown(unsigned char *dst, unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		*(dst + i) = *(src + i);
		i++;
	}
}

static void	ft_downtop(unsigned char *dst, unsigned char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i + 1 > 0)
	{
		*(dst + i) = *(src + i);
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tempdst;
	unsigned char	*tempsrc;

	tempdst = (unsigned char *)dst;
	tempsrc = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if ((dst - src) <= 0)
		ft_topdown(tempdst, tempsrc, n);
	else if ((dst - src) > 0)
		ft_downtop(tempdst, tempsrc, n);
	return (dst);
}
