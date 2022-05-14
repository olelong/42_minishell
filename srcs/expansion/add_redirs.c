/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:43:03 by afaure            #+#    #+#             */
/*   Updated: 2022/01/21 23:24:10 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"

/*
*si le maillon est un espace, supprime l'espace et renvoie le maillon suivant
*/
static inline t_wrd	*remove_space(t_wrd *name, t_cmd *cmd)
{
	t_wrd	*next;

	if (name->type == WHITESPACES)
	{
		next = name->next;
		lst_remove_one_wrd(&cmd->cmd, name);
		name = next;
	}
	return (name);
}

/*
*présume que redir et name se suivent, 
	connecte le maillon avant redir à celui d'apres name et vice versa
*/
static inline void	remove_from_cmd(t_wrd *redir, t_wrd *name)
{
	if (redir->prec)
		redir->prec->next = name->next;
	if (name->next)
		name->next->prec = redir->prec;
}

/*
*rajoute le maillon redir a la liste "redirs" de la commande cmd
*/
static inline void	add_to_redir_list(t_cmd *cmd, t_wrd *redir)
{
	t_wrd	*ptr;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		redir->prec = NULL;
	}
	else
	{
		ptr = cmd->redirs;
		while (ptr->next)
			ptr = ptr->next;
		redir->prec = ptr;
		ptr->next = redir;
	}
}
/*
* Ligne 50 si il n'y a rien dans les redirs 
	il suffit de mettre le maillon redir comme la tete
* Ligne 55 sinon, 
	il faut aller l'ajouter à la suite de la liste
*/

/*
* Retire le maillon redir et tout ceux qui forment le mot qui le suit 
	plus un potentiel maillon space entre les deux
* et mets le maillon redir dans la liste 
	des redirections à faire en mettant comme data le complément.
*/
t_wrd	*add_redirs(t_vars *vars, t_cmd *cmd, t_wrd *redir, t_wrd *name)
{
	t_wrd	*ret;

	name = remove_space(name, cmd);
	name = expand_wrd(vars, &cmd->cmd, name);
	ret = name->next;
	remove_from_cmd(redir, name);
	redir->data = name->data;
	free(name);
	redir->next = NULL;
	if (redir == cmd->cmd)
		cmd->cmd = ret;
	add_to_redir_list(cmd, redir);
	return (ret);
}
/* 
* Ligne 84 relier les maillon autour de la redir entre eux 
	pour retier nos maillons de la commande
* Ligne 85-87 mettre les données du maillon name dans le maillon redir 
	pour economiser de la mémoire et supprimer le maillon name
* Ligne 88 si le token redir est le premier de la commade
	je deplace la tete de la commande
* Ligne 90 Je rajoute le maillon redir a la liste des redirection à faire
* Je retourne un pointeur sur le maillon apres tout les maillons retirés
*/
