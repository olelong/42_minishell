/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 00:40:44 by olelong           #+#    #+#             */
/*   Updated: 2022/01/25 00:50:37 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

static int	add_type(t_type type, int i, t_vars *vars)
{
	int	start;

	start = 0;
	if (!lst_add_wrd(&vars->parsed_line, type, NULL))
		quit(1, ERR_MINISHELL, vars);
	start = i + 1;
	return (start);
}

static int	check_wrd(char *str, int i, int start, t_vars *vars)
{
	char	*tmp;

	tmp = copy(str + start, i - start, vars);
	if (!tmp)
		return (0);
	if (!lst_add_wrd(&vars->parsed_line, WRD, tmp))
	{
		free(tmp);
		return (0);
	}
	return (1);
}

static inline int	add_wrd(char *str, int i, int start, t_vars *vars)
{
	if (i != 0 && str[i - 1] != '$')
	{
		if (!check_wrd(str, i, start, vars))
			return (0);
	}
	return (1);
}

static inline int	add_wrd2(char *str, int i, int start, t_vars *vars)
{
	if (i != 0 && str[i - 1] != ' ' && str[i - 1] != '$')
	{
		if (!check_wrd(str, i, start, vars))
			return (0);
	}
	return (1);
}

/*
** Function that will parse what the user will write in the terminal
** following the use of a heredoc to be able to expand if we fall on
** a DOLLAR.
*/

int	parse_heredoc(char *str, t_vars *vars)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (!add_wrd(str, i, start, vars))
				return (0);
			start = add_type(WHITESPACES, i, vars);
		}
		else if (str[i] == '$')
		{
			if (!add_wrd2(str, i, start, vars))
				return (0);
			start = add_type(DOLLAR, i, vars);
		}
		i++;
	}
	if ((start == 0 || start != i) && !check_wrd(str, i, start, vars))
		return (0);
	return (1);
}
