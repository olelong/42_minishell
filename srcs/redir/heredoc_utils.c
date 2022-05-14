/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:04:53 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 00:56:52 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"
#include "../expansion/expansion.h"
#include "../parsing/parse.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"

char	*create_name(t_vars *vars)
{
	char	*temp;
	char	*path;

	temp = ft_itoa(vars->heredoc_counter);
	if (!temp)
		return (NULL);
	path = ft_strjoin(".heredoc", temp);
	free(temp);
	if (!path)
		return (NULL);
	return (path);
}

t_wrd	*expand_heredoc(t_vars *vars, t_wrd *parsed_line)
{
	t_wrd	*ptr;

	ptr = parsed_line;
	while (parsed_line)
	{
		if (parsed_line->type == DOLLAR && parsed_line->next
			&& (!is_valid_id(parsed_line->next->data)
				&& ft_strncmp(parsed_line->next->data, "?", 2) != 0))
		{
			parsed_line->type = WRD;
			parsed_line->data = ft_strdup("$");
			if (!parsed_line->data)
			{
				lst_destroy_wrd(parsed_line);
				quit(1, ERR_MINISHELL, vars);
			}
		}
		parsed_line = expand_wrd(vars, &ptr, parsed_line);
		parsed_line = parsed_line->next;
	}
	return (ptr);
}

t_wrd	*expand_limiter(t_vars *vars, t_wrd **head, t_wrd *wrd)
{
	t_wrd	*start;
	bool	in_quote;

	in_quote = false;
	start = wrd;
	while (wrd != NULL && valid_token(wrd) == true)
	{
		if (wrd->type == DOLLAR)
		{
			wrd->data = ft_strdup("$");
			if (!wrd->data)
				quit(1, ERR_EXPAND, vars);
		}
		if (wrd->type == QUOTE_IN)
			wrd = remove_quotes(vars, head, wrd);
		wrd = wrd->next;
	}
	start = cleanup_wrd(vars, head, start, wrd);
	return (start);
}

void	write_heredoc(int fd, t_wrd *word)
{
	while (word)
	{
		if (word->type == WHITESPACES)
			write(fd, " ", 1);
		else if (word->data)
			write(fd, word->data, ft_strlen(word->data));
		word = word->next;
	}
	write(fd, "\n", 1);
}

void	destroy_heredocs(t_vars *vars)
{
	char	*path;

	while (vars->heredoc_counter)
	{
		path = create_name(vars);
		if (!path)
			quit(1, ERR_MINISHELL, vars);
		unlink(path);
		free(path);
		vars->heredoc_counter--;
	}
}
