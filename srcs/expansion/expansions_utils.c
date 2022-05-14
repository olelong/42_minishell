/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:27:04 by afaure            #+#    #+#             */
/*   Updated: 2022/01/21 23:27:06 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../error_quit/errors.h"

bool	valid_token(t_wrd *wrd)
{
	if (wrd->type == WRD || wrd->type == DOLLAR
		|| wrd->type == QUOTE_IN || wrd->type == QUOTE_OUT)
		return (true);
	return (false);
}

/*
* ajoute une string contenant un espace aux tokens space entre les quotes
*/
t_wrd	*remove_quotes(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	(void) head;
	while (wrd->type != QUOTE_OUT)
	{
		if (wrd->type == WHITESPACES)
		{
			wrd->data = ft_strdup(" ");
			if (!wrd->data)
				quit(1, ERR_EXPAND, vars);
		}
		wrd = wrd->next;
	}
	return (wrd);
}
