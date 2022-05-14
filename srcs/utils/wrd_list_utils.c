/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:34:05 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 22:08:50 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
*fonction qui retourne un maillon wrd
*/
t_wrd	*lst_new_wrd(t_type type, char *data)
{
	t_wrd	*ret;

	ret = ft_calloc(1, sizeof(t_wrd));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->data = data;
	ret->prec = NULL;
	ret->next = NULL;
	return (ret);
}

/*
*fonction qui qajoute un maillon wrd a la fin de la chaine 
*/
int	lst_add_wrd(t_wrd **ptr, t_type type, char *data)
{
	t_wrd	*temp;
	t_wrd	*cpy;

	if ((*ptr)->type == UNKNOWN)
	{
		(*ptr)->type = type;
		(*ptr)->data = data;
		return (1);
	}
	cpy = *ptr;
	while (cpy->next)
		cpy = cpy->next;
	temp = lst_new_wrd(type, data);
	if (!temp)
		return (0);
	temp->prec = cpy;
	cpy->next = temp;
	return (1);
}

/*
*fonction qui ajoute un maillon wrd juste apres le maillon indiqué
*/
int	lst_add_after_wrd(t_wrd *ptr, t_type type, char *data)
{
	t_wrd	*temp;

	temp = lst_new_wrd(type, data);
	if (!temp)
		return (0);
	temp->prec = ptr;
	temp->next = ptr->next;
	if (temp->next)
		temp->next->prec = temp;
	ptr->next = temp;
	return (1);
}

/*
*detruit une liste chainee de wrd
*/
void	lst_destroy_wrd(t_wrd *head)
{
	while (head)
		lst_remove_one_wrd(&head, head);
}

/*
*retire et free un seul maillon d'une liste wrd
*/
void	lst_remove_one_wrd(t_wrd **head, t_wrd *wrd)
{
	t_wrd	*ptr;

	if (!wrd)
		return ;
	ptr = wrd;
	if (wrd != *head)
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
	if (ptr->data)
		free(ptr->data);
	free(ptr);
}
