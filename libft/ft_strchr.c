/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:26:10 by afaure            #+#    #+#             */
/*   Updated: 2020/11/20 13:34:13 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;
	size_t	i;
	size_t	len;

	i = 0;
	ret = (char *)s;
	len = ft_strlen(ret);
	while (i < len + 1)
	{
		if (ret[i] == c)
			return (ret + i);
		i++;
	}
	return (NULL);
}
