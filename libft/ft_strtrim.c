/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:25:21 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:50:17 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinside(int c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if ((unsigned char)set[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*trimmed;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_isinside(s1[start], set))
		start++;
	if (start >= end || !ft_strlen(s1))
	{
		trimmed = ft_calloc(1, sizeof(char));
		return (trimmed);
	}
	while (end && ft_isinside(s1[end], set))
		end--;
	trimmed = malloc((end - start + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, end - start + 2);
	return (trimmed);
}
