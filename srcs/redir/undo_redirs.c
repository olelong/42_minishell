/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:12:02 by afaure            #+#    #+#             */
/*   Updated: 2022/01/22 16:18:01 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../error_quit/errors.h"
//function to reconnect STDIN and STDOUT to the correct files
//returns 1 on failure, 0 on sucess
int	undo_redir(t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (cmd->exec.temp_stdin != -1)
	{
		if (dup2(cmd->exec.temp_stdin, STDIN_FILENO) != STDIN_FILENO)
		{
			write_err(ERR_REDIR, NULL, strerror(errno));
			ret = 1;
		}
		close(cmd->exec.temp_stdin);
		cmd->exec.temp_stdin = -1;
	}
	if (cmd->exec.temp_stdout != -1)
	{
		if (dup2(cmd->exec.temp_stdout, STDOUT_FILENO) != STDOUT_FILENO)
		{
			write_err(ERR_REDIR, NULL, strerror(errno));
			ret = 1;
		}
		close(cmd->exec.temp_stdout);
		cmd->exec.temp_stdout = -1;
	}
	return (ret);
}
