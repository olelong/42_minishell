/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 00:54:37 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:17:02 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../srcs/utils/utils.h"

int	do_heredoc(t_vars *vars, t_cmd *cmd, t_wrd *wrd)
{
	char	*temp;

	vars->heredoc_counter++;
	if (wrd->next->type == WHITESPACES)
		lst_remove_one_wrd(&cmd->cmd, wrd->next);
	temp = create_heredoc(vars, &cmd->cmd, wrd->next);
	if (!temp)
		return (0);
	return (1);
}

char	*create_heredoc(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	char	*path;
	char	*limiter;
	int		fd;

	path = create_name(vars);
	if (!path)
		return (NULL);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC,
			S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	wrd = expand_limiter(vars, head, wrd);
	limiter = wrd->data;
	wrd->data = path;
	if (!read_heredoc(vars, fd, limiter))
	{
		destroy_heredocs(vars);
		return (NULL);
	}
	return (path);
}
