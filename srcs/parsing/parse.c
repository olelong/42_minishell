/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:15 by olelong           #+#    #+#             */
/*   Updated: 2022/01/25 01:34:40 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that will manage the operator or the word.
** quote_i allows to know if we are in single or double quote.
** loop_id = index of i.
** is_double_op is a variable that will help to manage the operator has
** two characters like APPEND and HEREDOCS.
**
** If it is not an operator or the operator must be a word,
** is_double_op set to -1 because i later = is_double_op + 1
** so will be equal to 0.
** If we cross a redir, and the next character is the same,
** so we have a heredoc or an append, we set is_double_op to 1.
** If it is an operator, we add the operator to the word chain list.
**
** i = 2 if >> or << and i = 1 if an operator of one character.
**
** As long as it is not an operator or it is an operator not read in
** and it is not a space, we move on.
** If there is a word or adds it to the word list,
** str + is_double_op + 1 just takes into account the size of the word between
** two operators or before/after an operator and i - (is_double_op + 1))
** and the width of the word in the operator.
** Return the index of i of this function + the one of loop_id in parameter
** to update it so that when we exit this function the index is up to date.
*/

static int	manage_one_operator(char *str, int loop_i, int *quote_i, t_vars *v)
{
	int		i;
	int		is_double_op;
	int		ret;

	is_double_op = 0;
	ret = 0;
	if (!is_operator(str[0]) || is_operator_a_word(str[0], *quote_i))
		is_double_op = -1;
	else if (str[0] == '<' || str[0] == '>')
	{
		if (str[1] == str[0])
			is_double_op = 1;
	}
	if (is_double_op != -1)
		add_op(v, str, quote_i);
	i = is_double_op + 1;
	while ((!is_operator(str[i]) || is_operator_a_word(str[i], *quote_i))
		&& str[i] != ' ' && str[i])
		i++;
	if (i != is_double_op + 1)
		i = add_a_word(str, i, &is_double_op, v);
	return (i + loop_i);
}

/*
** This function handles pasted char blocks (without spaces):
** for example word$>>word.
*/

static int	manage_chars(char *str, int loop_id, int *quote_i, t_vars *vars)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i = manage_one_operator(&str[i], i, quote_i, vars);
	return (i + loop_id);
}

static void	check_wrd(char *str, int i, int start, t_vars *vars)
{
	char	*tmp;

	tmp = copy(str, i - start, vars);
	if (!tmp)
		quit(1, ERR_MINISHELL, vars);
	if (!lst_add_wrd(&vars->command_line->cmd, WRD, tmp))
		quit(1, ERR_MINISHELL, vars);
}

/*
** Function that traverses the string returned by readline()
** then if the character is not a space and i is not the first character,
** a space is added to the string list because that means that there must be
** at least one or more spaces before and I do the management of the
** operator or the word otherwise I increment.
*/

void	parser(char *str, int *quote_i, t_vars *vars)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (is_operator(str[i]) || str[i] == ' ')
		{
			if (start == 0 && i != 0)
				check_wrd(str, i, start, vars);
			if (str[i] == ' ')
			{
				i = check_space(str, i, *quote_i, vars);
				start = i + 1;
				i++;
			}
			i = manage_chars(&str[i], i, quote_i, vars);
			start = i;
		}
		else
			i++;
	}
	check_single_wrd(str, start, i - start, vars);
}
