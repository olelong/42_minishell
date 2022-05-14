/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:34:53 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 02:48:07 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"

t_wrd	*parse_var(t_vars *vars, t_wrd *wrd)
{
	char	*var;
	char	**tab;
	size_t	i;

	i = 0;
	var = wrd->data;
	tab = ft_split(var, ' ');
	if (!tab)
		quit(1, ERR_MINISHELL, vars);
	wrd->data = tab[i];
	free(var);
	i++;
	while (tab[i])
	{
		if (!lst_add_after_wrd(wrd, WRD, tab[i]))
		{
			destroy_tab((void **)tab);
			quit(1, ERR_MINISHELL, vars);
		}
		wrd = wrd->next;
		i++;
	}
	free(tab);
	return (wrd);
}

/* 
*  expansion sur un token DOLLAR
*  retourne un pointeur sur le maillon étendu
*/
static inline t_wrd	*variable_expansion(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	const char	*temp;

	(void)head;
	if (ft_strncmp(wrd->next->data, "?", ft_strlen(wrd->next->data)) == 0)
	{
		if (g_last_status < 0)
			g_last_status = -g_last_status;
		wrd->data = ft_itoa(g_last_status);
		if (!wrd->data)
			quit(1, ERR_EXPAND, vars);
	}
	else
	{
		temp = env_get(wrd->next->data, vars);
		if (temp)
			wrd->data = ft_strdup(temp);
		else
			wrd->type = UNKNOWN;
		if (temp && !wrd->data)
			quit(1, ERR_EXPAND, vars);
	}
	return (wrd);
}

t_wrd	*expand_parameter(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	if (!wrd->next || wrd->next->type == WHITESPACES
		|| wrd->next->type == QUOTE_OUT)
	{
		wrd->type = WRD;
		wrd->data = ft_strdup("$");
		if (!wrd->data)
			quit(1, ERR_MINISHELL, vars);
	}
	else if (wrd->next->type == WRD)
	{
		wrd = variable_expansion(vars, head, wrd);
		lst_remove_one_wrd(head, wrd->next);
	}
	else
		wrd->type = WRD;
	return (wrd);
}
/* 
* Si il n'y a rien ou un space ou une fermeture de quote
	Le token devient un simple wrd avec "$" comme data

* Si le token d'apres est un wrd
	Je vais chercher ce wrd dans env et je met le retour de env dans mon token
	Je supprime le token qui suit
* Si c'est un pipe ou un guillemet ou n'importe quoi d'autre
	je met le token en wrd vide
*/
