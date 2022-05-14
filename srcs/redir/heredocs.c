/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:16:45 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:16:29 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"
#include "../expansion/expansion.h"
#include "../parsing/parse.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"
#include "../signals/signals_minishell.h"

/*
** function to check through all the commands if there are anny heredocs,
** to expand the limiter and creates the tmp files
** return 0 on success 1 on error
*/

int	check_heredoc(t_vars *vars)
{
	t_wrd	*wrd;
	t_cmd	*ptr;

	init_heredoc_signal();
	ptr = vars->command_line;
	while (ptr)
	{
		wrd = ptr->cmd;
		while (wrd)
		{
			if (wrd->type == REDIR_HEREDOC)
			{
				if (!do_heredoc(vars, ptr, wrd))
					return (0);
			}
			wrd = wrd->next;
		}
		ptr = ptr->next;
	}
	init_non_interactive_signal();
	return (1);
}

static inline int	close_free(int fd, char *limiter, char *line)
{
	if (line)
		free(line);
	if (limiter)
		free(limiter);
	close(fd);
	return (0);
}

static void	close_free_quit(int fd, char *limiter, char *line, t_vars *vars)
{
	close_free(fd, limiter, line);
	quit(1, ERR_MINISHELL, vars);
}

static inline void	write_line(t_vars *vars, int fd, char *limiter, char *line)
{
	vars->parsed_line = lst_new_wrd(UNKNOWN, NULL);
	if (!vars->parsed_line)
		close_free_quit(fd, limiter, line, vars);
	if (!parse_heredoc(line, vars))
		close_free_quit(fd, limiter, line, vars);
	vars->parsed_line = expand_heredoc(vars, vars->parsed_line);
	write_heredoc(fd, vars->parsed_line);
	lst_destroy_wrd(vars->parsed_line);
	vars->parsed_line = NULL;
}

int	read_heredoc(t_vars *vars, int fd, char *limiter)
{
	char	*line;

	line = readline(">");
	while (line)
	{
		if (g_last_status < 0)
		{
			g_last_status = -g_last_status;
			return (close_free(fd, limiter, line));
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			close_free(fd, limiter, line);
			return (1);
		}
		write_line(vars, fd, limiter, line);
		free(line);
		line = readline(">");
	}
	close_free(fd, limiter, line);
	write_err(ERR_MINISHELL, NULL, ERR_EOF);
	return (0);
}
