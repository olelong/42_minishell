/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:06:40 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:10:04 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_size;

	dest_size = 0;
	while (*dst && dest_size < size)
	{
		dst++;
		dest_size++;
	}
	if (size > dest_size)
		ft_strlcpy(dst, src, size - dest_size);
	return (dest_size + ft_strlen(src));
}
