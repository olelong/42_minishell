/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:50:36 by olelong           #+#    #+#             */
/*   Updated: 2022/01/24 21:41:35 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Function that checks if the command line is empty ( or filled
** only with spaces)
*/

int	is_empty(char *str, int end)
{
	int	i;

	if (end == 0)
		return (0);
	i = 0;
	while (str[i] && (i < end || end == -1))
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
