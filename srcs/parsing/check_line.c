/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:21:01 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 23:20:25 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that will add the word if there were no specific characters
** in the command line.
*/

void	check_single_wrd(char *str, int start, int len, t_vars *vars)
{
	char	*tmp;

	if (start == 0)
	{
		tmp = copy(str, len, vars);
		if (!tmp)
			quit(1, ERR_MINISHELL, vars);
		if (!lst_add_wrd(&vars->command_line->cmd, WRD, tmp))
			quit(1, ERR_MINISHELL, vars);
	}
}

/*
** Function that will check the spaces and depending on whether they are in
** quotes or not add several spaces or only one.
*/

int	check_space(char *str, int i, int quote_i, t_vars *vars)
{
	(void)vars;
	if (quote_i % 2 == 1 && str[i] == ' ')
	{
		if (!lst_add_wrd(&vars->command_line->cmd, WHITESPACES, NULL))
			quit(1, ERR_MINISHELL, vars);
	}
	else
	{
		if (!lst_add_wrd(&vars->command_line->cmd, WHITESPACES, NULL))
			quit(1, ERR_MINISHELL, vars);
		while (str[i + 1] == ' ' && str[i])
			i++;
	}
	return (i);
}

int	add_a_word(char	*str, int i, int *is_double_op, t_vars *vars)
{
	char	*tmp;

	tmp = copy(str + *is_double_op + 1, i - (*is_double_op + 1), vars);
	if (!tmp)
		quit(1, ERR_MINISHELL, vars);
	if (!lst_add_wrd(&vars->command_line->cmd, WRD, tmp))
	{
		free(tmp);
		quit(1, ERR_MINISHELL, vars);
	}
	return (i);
}
