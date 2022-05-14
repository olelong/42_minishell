/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:52:28 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 15:55:57 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../error_quit/errors.h"

//pipe[0] read
//pipe[1] write

int	exec_tree(t_vars *vars, t_cmd *head, int fd_stdin)
{
	if (head->type == CMD && !head->exec.in_pipe)
		return (search_exec_command(vars, head, false));
	else if (head->type == CMD && head->exec.in_pipe)
		return (exec_last_cmd(vars, head, fd_stdin));
	else if (head->type == PIPE)
		return (exec_pipe(vars, head, fd_stdin));
	return (0);
}
// Ligne 20 une simple execution de commande si on est pas dans un pipe
// LIgne 22 si on est dans un pipe ( avec stdin modifié )

/*
* utilise pipe et fork pour créer un process 
* pour executer la commande a sa gauche, 
* relier son entrée au pipe d'avant si il y en a un
* relier la sortie au pipe d'apres
* puis apres continuer de descendre l'arbre avec le commande ou le pipe a droite
*/
int	exec_pipe(t_vars *vars, t_cmd *head, int fd_stdin)
{
	int	pype[2];

	head->exec.right_child->exec.in_pipe = true;
	head->exec.left_child->exec.in_pipe = true;
	if (pipe(pype) == -1)
		return (1);
	head->exec.left_child->exec.pid = fork();
	if (head->exec.left_child->exec.pid == 0)
		exit(exec_left_child(vars, head->exec.left_child, pype, fd_stdin));
	else if (head->exec.left_child->exec.pid > 0)
	{
		if (fd_stdin != STDIN_FILENO)
			close(fd_stdin);
		close(pype[1]);
		return (exec_tree(vars, head->exec.right_child, pype[0]));
	}
	else if (head->exec.left_child->exec.pid == -1)
		close_pipe(pype);
	return (1);
}
/* Ligne 47 Appel a fork
   Ligne 48-49 dans le child, executer la partie gauche du pipe
   Ligne 50-56 dans le parent, fermer le pipe d'avant et l'entrée du pipe actuel
	continuer de descendre l'arbre en donnant la sortie du pipe
   Ligne 57-62 en cas d'erreur, fermer le pipe et return >0
*/

//lance la fonction d'execution des commandes 
//en reliant les entres sorties aux pipes et ferme les fd non utilisés
int	exec_left_child(t_vars *vars, t_cmd *cmd, int pype[2], int fd_stdin)
{
	int	ret;

	dup2(fd_stdin, STDIN_FILENO);
	dup2(pype[1], STDOUT_FILENO);
	close_pipe(pype);
	ret = search_exec_command(vars, cmd, true);
	free_all(vars);
	return (ret);
}

//doit fork puis executer la derniere commande d'un pipe
int	exec_last_cmd(t_vars *vars, t_cmd *cmd, int fd_stdin)
{
	int	ret;

	cmd->exec.pid = fork();
	if (cmd->exec.pid == 0)
	{
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
		ret = search_exec_command(vars, cmd, true);
		free_all(vars);
		exit(ret);
	}
	if (cmd->exec.pid > 0)
	{
		close(fd_stdin);
		return (0);
	}
	if (cmd->exec.pid == -1)
		return (1);
	return (0);
}
