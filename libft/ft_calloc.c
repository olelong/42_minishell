/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:54:02 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:40:32 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t nsize)
{
	void	*ret;

	ret = malloc(nmemb * nsize);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, nmemb * nsize);
	return (ret);
}
