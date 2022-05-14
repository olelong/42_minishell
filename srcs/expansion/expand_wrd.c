/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wrd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:01:19 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:26:35 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"
#include "../../libft/libft.h"

static inline void	add_to_temp(t_vars *vars, t_wrd *ptr, char	**temp)
{
	*temp = ft_realloc(*temp, ptr->data);
	if (!*temp)
		quit(1, ERR_EXPAND, vars);
}

/*
*un mot est défini comme n'importe quoi entre espaces
* la fonction expand wrd aura modifié des tokens
	pour expand des variables d'env, supprimer des quote etc...
	jusque au prochain token space
* cette fonction créé un seul token word contenant tout cela
	en supprimant les tokens inutiles et le retourne
*/
t_wrd	*cleanup_wrd(t_vars *vars, t_wrd **head, t_wrd *start, t_wrd *end)
{
	char	*temp;
	t_wrd	*ptr;

	temp = NULL;
	if (start == end || start->next == end)
		return (start);
	while (start->next != end)
	{
		if (start->data || start->type == QUOTE_IN)
			add_to_temp(vars, start, &temp);
		ptr = start->next;
		lst_remove_one_wrd(head, start);
		start = ptr;
	}
	if (start->data && temp)
	{
		add_to_temp(vars, start, &temp);
		free(start->data);
	}
	start->data = temp;
	start->type = WRD;
	return (start);
}

/*
* fonction qui va expand le mot commencant par le token envoyé
* elle retourne le maillon crée par l'extension
*a retenir qu'un wrd est composé d'absolument tout entre deux spaces ( ou redir)
*/
t_wrd	*expand_wrd(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	t_wrd	*start;
	bool	in_quote;

	in_quote = false;
	start = wrd;
	while (wrd != NULL && (valid_token(wrd) || in_quote))
	{
		if (wrd->type == DOLLAR)
			wrd = expand_parameter(vars, head, wrd);
		else if (wrd->type == QUOTE_IN)
			in_quote = true;
		else if (wrd->type == QUOTE_OUT)
			in_quote = false;
		wrd = wrd->next;
	}
	wrd = start;
	while (wrd != NULL && valid_token(wrd) == true)
	{
		if (wrd->type == QUOTE_IN)
			wrd = remove_quotes(vars, head, wrd);
		wrd = wrd->next;
	}
	start = cleanup_wrd(vars, head, start, wrd);
	return (start);
}
/*
* Ligne 65 premier passage pour expand des dollar 
	( avec in quote qui permet d'ignorer les spaces)
* Ligne 76 second passage pour supprimer les quotes
* Cette fonction crée/modifie plusieurs token 
	pour l'expansion de parametre puis le quote removal
	( quote removal qui enfait est juste le fait 
	de donner aux tokens space une string contenant "spaces"
	car le cleanup supprimera les token sans data comme les quotes)
* Puis la fonctin cleanup concatene le tout et supprime tout les tokens a par un 
	pour qu'il n'y en ai plus qu'un
*/
