/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:12:53 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:42:03 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	if (!n)
		return (NULL);
	while (*big && i <= n - little_len)
	{
		if (!(ft_strncmp(big, little, little_len)))
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
