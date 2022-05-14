/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:58:31 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 21:53:54 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

/*
** Function that will copy a word from the string according to a start. 
** start(which is the index of the last operator(found) and an i
** which is the index of the new operator found in the string.
*/

char	*copy(char *str, int start, t_vars *vars)
{
	char	*copy;

	copy = ft_calloc(start + 1, sizeof(char));
	if (!copy)
		quit(1, ERR_MINISHELL, vars);
	if (!str || start < 0)
		return (NULL);
	ft_strlcpy(copy, str, start + 1);
	return (copy);
}

t_cmd	*init_parser(void)
{
	t_wrd	*word;
	t_cmd	*ret;

	word = lst_new_wrd(UNKNOWN, NULL);
	if (!word)
		return (NULL);
	ret = lst_new_cmd(CMD, word);
	if (!ret)
		free (word);
	return (ret);
}
