/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:07:56 by afaure            #+#    #+#             */
/*   Updated: 2022/01/03 16:31:50 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* initialise les varaibles utilisées pendant l'exec */
void	init_exec(t_vars *vars)
{
	t_cmd	*cmd;

	cmd = vars->command_line;
	while (cmd)
	{
		cmd->exec.in_pipe = false;
		cmd->exec.pid = 0;
		cmd->exec.temp_stdin = -1;
		cmd->exec.temp_stdout = -1;
		cmd->exec.left_child = NULL;
		cmd->exec.right_child = NULL;
		cmd = cmd->next;
	}
	create_tree(vars);
}

/* en partant d'un token renvoie le prochain token de type PIPE 
	ou null si il n'y en a pas */
static void	*find_next_pipe(t_cmd *tok)
{
	while (tok->next)
	{
		if (tok->type == PIPE)
			return (tok);
		tok = tok->next;
	}
	return (tok);
}

/*créé un arbre binaire avec la liste de token CMD et PIPE */
int	create_tree(t_vars *vars)
{
	t_cmd	*ptr;

	ptr = vars->command_line;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			ptr->exec.left_child = ptr->prec;
			ptr->exec.right_child = find_next_pipe(ptr->next);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

/* retourne la tete d'un arbre binaire crée par create_tree */
t_cmd	*get_tree_head(t_cmd *cmd)
{
	t_cmd	*ptr;

	ptr = cmd;
	while (ptr->next)
	{
		if (ptr->type == PIPE)
			return (ptr);
		ptr = ptr->next;
	}
	return (ptr);
}
