/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:13:27 by afaure            #+#    #+#             */
/*   Updated: 2021/01/20 11:52:38 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*ret;

	ret = NULL;
	i = 0;
	len = ft_strlen(s);
	while (i < len + 1)
	{
		if (s[i] == c)
			ret = (char *)s + i;
		i++;
	}
	return (ret);
}
