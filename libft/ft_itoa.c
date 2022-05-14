/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:43:57 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:51:34 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	temp;
	char	*ret;
	int		i;

	i = 0;
	temp = n;
	if (temp < 0)
		temp = -temp;
	ret = malloc(13 * sizeof(char));
	if (!ret)
		return (NULL);
	while (temp > 9)
	{
		ret[i++] = (temp % 10) + '0';
		temp = temp / 10;
	}
	ret[i++] = temp + '0';
	if (n < 0)
		ret[i++] = '-';
	ret[i] = '\0';
	return (ft_rev_str(ret));
}
