/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:41:17 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:09:29 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

/*
*free str1, alloue de la mémoire assez grande pour les deux
*/
char	*ft_realloc(char *str1, const char *str2)
{
	size_t	total_len;
	size_t	len1;
	size_t	len2;
	char	*ret;

	len1 = 0;
	len2 = 0;
	if (str1)
		len1 = ft_strlen(str1);
	if (str2)
		len2 = ft_strlen(str2);
	total_len = len1 + len2;
	ret = malloc((total_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	if (str1)
		ft_strlcpy(ret, str1, len1 + 1);
	if (str2)
		ft_strlcat(ret, str2, total_len + 1);
	if (str1)
		free(str1);
	return (ret);
}

/*
*fonction pour free des tableaux termine par un pointeur NULL
*/

void	destroy_tab(void **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

/*
** fonction qui remove du tableau l'element elem et le free si demande
*/

void	remove_str_tab(char **tab, char *elem, bool do_free)
{
	size_t	i;

	i = 0;
	while (tab[i] && ft_strncmp(tab[i], elem, ft_strlen(elem) != 0))
		i++;
	if (!tab[i])
		return ;
	if (do_free)
		free(tab[i]);
	while (tab[i])
	{
		tab[i] = tab[i + 1];
		i++;
	}
}

int	event(void)
{
	return (0);
}
