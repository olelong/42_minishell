/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:27:34 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:53:03 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (start >= ft_strlen(s))
	{
		ret = malloc(1 * sizeof(char));
		if (!ret)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	while (s[i + start] && i < len)
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	len = 0;
	while (len < i)
	{
		ret[len] = s[len + start];
		len++;
	}
	ret[len] = '\0';
	return (ret);
}
