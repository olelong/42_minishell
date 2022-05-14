/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:49:00 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 22:01:28 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

/*
** Function that returns 0 or 1 depending on whether it is equal to one
** of these characters.
** These are the characters with which there can be syntax errors.
*/

static int	is_op_syntax_error(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Function that will print the error message with the character that
** is the problem between ''. token allows to give operators
** like : $ " ' | < > and str : >> <<.s
** STDERR_FILENO = 2 : stderr.
*/

int	print_syntax_error(char token, char *str)
{
	ft_putstr_fd("msh: syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		write(STDERR_FILENO, &token, 1);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_last_status = 2;
	return (1);
}

/*
** Function that allows you to compare two characters of a string to
** check the number of times in the following we have the same operator.
*/

static int	is_same(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c && str[i])
		i++;
	return (i);
}

/*
** Function that checks if the redirs exceed their max of 2 or if there is
** more than one pipe in a row.
*/

static int	check_same_len(char *str, int i, char c)
{
	if (is_same(&str[i], '>') > 2)
		return (print_syntax_error(0, ">>"));
	else if (is_same(&str[i], '<') > 2)
		return (print_syntax_error(0, "<<"));
	else if (is_same(&str[i], '|') > 1)
		return (print_syntax_error(0, "||"));
	else if (c != -1)
		if (c != str[i] || (i != 0 && str[i - 1] == ' '))
			return (print_syntax_error(str[i], NULL));
	return (0);
}

/*
** Function that will handle syntax errors such as: >>> <<< || .
** c allows to know what was the last character before the spaces.
**
** If the first character is a PIPE -> syntax error.
** If the last character was a syntax error operator,
** If the current character is different from the old one 
** (= two syntax error operators that are consecutive but not 
** append or heredoc) OR if there is a space before
** (= two operators of syntax error operators separated by spaces
** (this is an error in all cases)),
** The syntax error operator is stored in c,
** c = -1; = the last character (except space) was not a syntax error operator
** allows to manage errors such as : > >>
** We skip finally the spaces.
*/

int	syntax_error(char *str)
{
	char	c;
	int		i;

	c = -1;
	i = 0;
	while (str[i])
	{
		if (str[0] == '|')
			return (print_syntax_error(0, "|"));
		if (is_op_syntax_error(str[i]))
		{
			if (check_same_len(str, i, c))
				return (1);
			c = str[i];
		}
		else
			c = -1;
		i++;
		while (str[i] == ' ' && str[i])
			i++;
	}
	if (c != -1)
		return (print_syntax_error('\0', "newline"));
	return (0);
}
