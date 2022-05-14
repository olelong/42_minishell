/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:16:07 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:49:05 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*next_i(char const *s, char c, char type)
{
	if (type == 's')
		while (*s == c && *s)
			s++;
	else
		while (*s != c && *s)
			s++;
	return ((char *)s);
}

static int	find_nb_strs(char const *s, char c)
{
	int		nb_strs;

	nb_strs = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		nb_strs++;
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
	}
	return (nb_strs);
}

static void	cpy_substr(char const *s, char c, char *cpy)
{
	char	*s_end;

	s_end = next_i(s, c, 'c');
	while (s < s_end)
	{
		*cpy = *s;
		s++;
		cpy++;
	}
	*cpy = 0;
}

char	**ft_split(char const *s, char c)
{
	int		nb_strs;
	char	**tab;
	int		i;

	if (!s)
		return (0);
	nb_strs = find_nb_strs(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab)
		return (0);
	i = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		tab[i] = (char *)malloc(sizeof(char) * ((next_i(s, c, 'c') - s) + 1));
		if (!tab[i])
			return (free_split(tab));
		cpy_substr(s, c, tab[i]);
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
		i++;
	}
	tab[i] = 0;
	return (tab);
}
