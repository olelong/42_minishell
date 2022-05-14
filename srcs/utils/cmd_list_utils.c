/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:36:41 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 15:26:37 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
*fonction qui retourne un mailloncmd
*/
t_cmd	*lst_new_cmd(t_cmd_type type, t_wrd *cmd)
{
	t_cmd	*ret;

	ret = ft_calloc(1, sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->cmd = cmd;
	ret->redirs = NULL;
	ret->prec = NULL;
	ret->next = NULL;
	return (ret);
}

/*
*fonction qui qjoute un maillon cmd à la fin de la chaine
*/
int	lst_add_cmd(t_cmd *ptr, t_cmd_type type, t_wrd *cmd)
{
	t_cmd	*temp;

	while (ptr->next)
		ptr = ptr->next;
	temp = lst_new_cmd(type, cmd);
	if (!temp)
		return (0);
	temp->prec = ptr;
	ptr->next = temp;
	return (1);
}

/*
*fonction qui ajoute un maillon cmd juste apres le maillon indiqué
*/
int	lst_add_after_cmd(t_cmd *ptr, t_cmd_type type, t_wrd *cmd)
{
	t_cmd	*temp;

	temp = lst_new_cmd(type, cmd);
	if (!temp)
		return (0);
	temp->prec = ptr;
	temp->next = ptr->next;
	temp->next->prec = temp;
	ptr->next = temp;
	return (1);
}

/*
*detruit une liste entiere de cmd
*/
void	lst_destroy_cmd(t_cmd *head)
{
	while (head)
		lst_remove_one_cmd(&head, head);
}

/*
*retire et free un seul maillon d'une liste cmd
*/
void	lst_remove_one_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*ptr;

	ptr = *head;
	while (ptr->next && ptr != cmd)
		ptr = ptr->next;
	if (cmd != *head)
	{
		if (ptr->prec)
			ptr->prec->next = ptr->next;
		if (ptr->next)
			ptr->next->prec = ptr->prec;
	}
	else
	{
		*head = ptr->next;
		if (*head)
			(*head)->prec = NULL;
	}
	lst_destroy_wrd(ptr->cmd);
	lst_destroy_wrd(ptr->redirs);
	free(ptr);
}
