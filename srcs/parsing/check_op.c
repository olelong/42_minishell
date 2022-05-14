/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:52:26 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 21:53:32 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that returns quote_in or quote_out depending on whether 
** we enter or exit of a quote. 
** We modify quote_i according to whether it is an entry, exit, double or
** simple quote. If we are in single quote_in quote_i will be == 1 and
** if double quote_in quote_i will be == 3.
** Initialize i to 0 before its first call.
*/

t_type	check_quote(char c, int *quote_i)
{
	if (c == '\'' && *quote_i % 2 == 0)
	{
		*quote_i = 1;
		return (QUOTE_IN);
	}
	else if (c == '\'' && *quote_i == 1)
	{
		*quote_i = 2;
		return (QUOTE_OUT);
	}
	else if (c == '\"' && *quote_i % 2 == 0)
	{
		*quote_i = 3;
		return (QUOTE_IN);
	}
	else if (c == '\"' && *quote_i == 3)
	{
		*quote_i = 4;
		return (QUOTE_OUT);
	}
	else if (c == '\'' && *quote_i == 3)
		return (WRD);
	else
		return (UNKNOWN);
}

/*
** Function that will return an error if a quote is not closed.
*/

int	quote_is_open(int quote_i, t_vars *vars)
{
	lst_destroy_cmd(vars->command_line);
	if (quote_i == 1)
		return (print_syntax_error('\'', NULL));
	else
		return (print_syntax_error('\"', NULL));
}

/*
** Function which add a simple quote as WRD when are in double quotes.
*/

void	add_simple_quote(t_vars *vars, t_wrd **word)
{
	char	*tmp;

	tmp = ft_strdup("\'");
	if (!tmp)
		quit(1, ERR_MINISHELL, vars);
	if (!lst_add_wrd(word, WRD, tmp))
		quit(1, ERR_MINISHELL, vars);
}

/*
** Function that returns the t_type that corresponds to the operator found.
*/

t_type	get_type(char *str, int *quote_i)
{
	if (str[0] == '>' && str[1] == '>')
		return (REDIR_APPEND);
	else if (str[0] == '<' && str[1] == '<')
		return (REDIR_HEREDOC);
	else if (str[0] == '>')
		return (REDIR_RIGHT);
	else if (str[0] == '<')
		return (REDIR_LEFT);
	else if (str[0] == '\'' || str[0] == '\"')
		return (check_quote(str[0], quote_i));
	else if (str[0] == '$')
		return (DOLLAR);
	else if (str[0] == '|')
		return (PIPE_);
	else
		return (WRD);
}

/*
** Foncion that returns 0 or 1 depending on whether the condition is met,
** depending on if the character is an operator or not.
*/

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|'
		|| c == '$' || c == '\'' || c == '\"');
}
