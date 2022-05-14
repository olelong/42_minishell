/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:29:37 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 02:19:12 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../error_quit/errors.h"
#include "../utils/utils.h"

void	check_sigint(t_cmd *cmd)
{
	bool	noprint;
	bool	newline;

	newline = false;
	noprint = false;
	while (cmd)
	{
		if (cmd->exec.pid == 128 + SIGSEGV || cmd->exec.pid == 128 + SIGQUIT)
			noprint = true;
		if (cmd->exec.pid == 128 + SIGINT && !noprint)
			newline = true;
		if (cmd->exec.pid == 128 + SIGINT && !cmd->next)
			newline = false;
		cmd = cmd->next;
	}
	if (newline)
		write(1, "\n", 1);
}

/* passe dans tout les maillons cmd et 
* wait les process qui ont été crées pendant le piping
* ecris un message si le process a exit avec un des signaux demandant un message
*/
void	wait_all(int *ret, t_cmd *cmd)
{
	t_cmd	*ptr;

	ptr = cmd;
	while (cmd)
	{
		if (cmd->type == CMD)
		{
			if (cmd->next)
				wait_child(cmd->exec.pid, ret, 0);
			else
				wait_child(cmd->exec.pid, ret, 1);
			cmd->exec.pid = *ret;
		}
		cmd = cmd->next;
	}
	check_sigint(ptr);
}

/* wait un process puis assigne a ret la bonne valeur de retour*/
void	wait_child(pid_t pid, int *ret, bool print_signal)
{
	waitpid(pid, ret, 0);
	if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	else if (WIFSIGNALED(*ret))
	{
		*ret = WTERMSIG(*ret);
		*ret += 128;
		if (print_signal)
			write_signal(*ret);
	}
}

/*close les deux fd d'un pipe */
void	close_pipe(int pype[2])
{
	close(pype[0]);
	close(pype[1]);
}
