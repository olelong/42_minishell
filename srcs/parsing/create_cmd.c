/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:49:53 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 21:53:40 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that parses the word chain list and retrieves the cmd
** as soon as it crosses a PIPE.
** We keep the head of word then we use ptr to cross the chain list.
** If the current ptr is a pipe,
** we add the command pipe, and the following command.
** We add the precedent link in tmp so the link before the pipe,
** We remove the link between pipe to relink with the link after pipe.
** We add a command PIPE and we add the next command.
** We set the link to the precedent next at NULL
** and ptr set to the next of tmp.
** We advance ptr to the next link.
*/

void	parse_cmd(t_cmd **cmd, t_wrd **word, t_vars *vars)
{
	t_wrd	*ptr;
	t_wrd	*tmp;

	ptr = *word;
	while (ptr)
	{
		if (ptr->type == PIPE_)
		{
			tmp = ptr->prec;
			lst_remove_one_wrd(word, ptr);
			if (!lst_add_cmd(*cmd, PIPE, NULL))
				quit(1, ERR_MINISHELL, vars);
			if (!lst_add_cmd(*cmd, CMD, tmp->next))
				quit(1, ERR_MINISHELL, vars);
			tmp->next->prec = NULL;
			ptr = tmp->next;
			tmp->next = NULL;
		}
		ptr = ptr->next;
	}
}
