/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:48:24 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:14:26 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strljoin(char const *s1, char const *s2, size_t size)
{
	size_t	total_len;
	char	*ret;

	total_len = ft_strlen(s1) + size;
	ret = malloc((total_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	ft_strlcat(ret, s2, total_len + 1);
	return (ret);
}
