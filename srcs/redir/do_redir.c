/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:43:02 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:14:11 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../error_quit/errors.h"

/*
*reads through the redirs list, return 0 on success 1 on failure
*/
int	do_redir(t_cmd *cmd, t_wrd *redirs)
{
	char	*path;

	while (redirs)
	{
		path = redirs->data;
		if (!path)
		{
			write_err(ERR_MINISHELL, NULL, ERR_AMBIGUOUS);
			return (1);
		}
		if (redirs->type == REDIR_RIGHT || redirs->type == REDIR_APPEND)
		{
			if (do_redir_right(path, &cmd->exec.temp_stdout,
					redirs->type == REDIR_APPEND) == 1)
				return (1);
		}
		else if (redirs->type == REDIR_LEFT || redirs->type == REDIR_HEREDOC)
		{
			if (do_redir_left(path, &cmd->exec.temp_stdin) == 1)
				return (1);
		}
		redirs = redirs->next;
	}
	return (0);
}

int	do_redir_right(const char *path, int *temp, bool append)
{
	if (*temp == -1)
		*temp = dup(STDOUT_FILENO);
	if (*temp == -1)
	{
		write_err(ERR_REDIR, NULL, strerror(errno));
		return (1);
	}
	if (redir_out(path, append) == FAILURE)
	{
		close(*temp);
		*temp = -1;
		return (1);
	}
	return (0);
}

int	do_redir_left(const char *path, int *temp)
{
	if (*temp == -1)
		*temp = dup(STDIN_FILENO);
	if (*temp == -1)
	{
		write_err(ERR_REDIR, NULL, strerror(errno));
		return (1);
	}
	if (redir_in(path) == FAILURE)
	{
		close(*temp);
		*temp = -1;
		return (1);
	}
	return (0);
}

int	redir_out(const char *path, bool append)
{
	int	fd;

	if (append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND,
				S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC,
				S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		write_err(ERR_MINISHELL, path, strerror(errno));
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redir_in(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write_err(ERR_MINISHELL, path, strerror(errno));
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
