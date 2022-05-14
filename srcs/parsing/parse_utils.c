/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 01:32:21 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:34:36 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that will check if in quotes an operator must
** be read as such or if it should be read as a WRD.
**
** quote_i == 1 If we are in a simple quote in,
** and c == '\' a simple quote is a quote out and not a word
** however operators are words.
** quote_i == 3 If we are in a double quote in,
** and c == '\"' a double quote is a quote out so not a word
** otherwise the operators are words.
*/

int	is_operator_a_word(char c, int quote_i)
{
	if (is_operator(c))
	{
		if (quote_i != 1 && c == '$')
			return (0);
		if (quote_i == 1)
		{
			if (c == '\'')
				return (0);
			return (is_operator(c));
		}
		if (quote_i == 3)
		{
			if (c == '\"')
				return (0);
			if (c == '\'')
				return (0);
			return (is_operator(c));
		}
	}
	return (0);
}

void	add_op(t_vars *vars, char *str, int *quote_i)
{
	int	ret;

	ret = 0;
	ret = get_type(str, quote_i);
	if (str[0] == '\'' && ret == WRD)
		add_simple_quote(vars, &vars->command_line->cmd);
	else
	{
		if (!lst_add_wrd(&vars->command_line->cmd, ret, NULL))
			quit(1, ERR_MINISHELL, vars);
	}
}
