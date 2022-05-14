/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:25:49 by afaure            #+#    #+#             */
/*   Updated: 2021/08/17 00:46:44 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(unsigned int nbr, int base_len)
{
	int	ret;

	if (!nbr)
		return (1);
	ret = 0;
	while (nbr)
	{
		nbr /= base_len;
		ret++;
	}
	return (ret);
}

static void	ft_recur(int length, unsigned int nbr, char *base, char *ret)
{
	size_t		base_len;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
		ft_recur(length - 1, nbr / base_len, base, ret);
	ret[length] = base[nbr % base_len];
}

char	*ft_itoa_base(int nbr, char *base, int unsign)
{
	char				*ret;
	unsigned int		temp;
	size_t				base_len;
	int					neg;

	neg = 0;
	base_len = ft_strlen(base);
	if (nbr < 0 && !unsign)
	{
		neg = 1;
		temp = -nbr;
	}
	else
		temp = nbr;
	ret = ft_calloc(length(temp, base_len) + neg + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_recur(length(temp, base_len) + neg - 1, temp, base, ret);
	if (neg)
		ret[0] = '-';
	return (ret);
}
