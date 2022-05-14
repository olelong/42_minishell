/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:01:37 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:55:24 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"

static inline t_wrd	*separate_redirs(t_vars *vars, t_cmd *cmd, t_wrd *ptr)
{
	if (ptr->type == REDIR_APPEND || ptr->type == REDIR_HEREDOC
		|| ptr->type == REDIR_LEFT || ptr->type == REDIR_RIGHT)
		ptr = add_redirs(vars, cmd, ptr, ptr->next);
	else
		ptr = ptr->next;
	return (ptr);
}

t_cmd	*expand_cmd(t_cmd *cmd, t_vars *vars)
{
	t_wrd	*ptr;

	ptr = cmd->cmd;
	while (ptr)
		ptr = separate_redirs(vars, cmd, ptr);
	ptr = cmd->cmd;
	while (ptr)
	{
		ptr = expand_wrd(vars, &cmd->cmd, ptr);
		ptr = ptr->next;
	}
	ptr = cmd->cmd;
	while (ptr)
	{
		if (ptr->type == DOLLAR)
			ptr = parse_var(vars, ptr);
		ptr = ptr->next;
	}
	cleanup_cmd(&cmd->cmd);
	return (cmd);
}
/* 
Ligne 21 si il ya une redirection, 
	mettre le token et son complément dans la liste des redirections
Ligne 29 effectuer les expansionssur chacun des mots 
	( la fonction expand wrd est susceptible de changer les maillons
		donc elle retourne un pointeur sur le maillon créé par l'expansion
		garantissant que celui d'apres n'a pas encore été traité)
*/

void	cleanup_cmd(t_wrd **head)
{
	t_wrd	*ptr;
	t_wrd	*temp;

	ptr = *head;
	while (ptr)
	{
		if (!ptr->data)
		{
			temp = ptr->next;
			lst_remove_one_wrd(head, ptr);
			ptr = temp;
		}
		else
			ptr = ptr->next;
	}
}
