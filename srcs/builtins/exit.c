/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:00:57 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 19:08:30 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../error_quit/errors.h"
#include "../utils/utils.h"

static bool	isonlynum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ft_exit(char **argv, t_vars *vars)
{
	argv++;
	if (*argv)
	{
		if (*(argv + 1))
		{
			write_err(ERR_EXIT, NULL, ERR_TOO_MANY);
			return (1);
		}
		if (!isonlynum(*argv))
		{
			write_err(ERR_EXIT, *argv, ERR_NOT_NUMERIC);
			g_last_status = WRONG_USE;
		}
		else
			g_last_status = ft_atoi(*argv);
	}
	argv--;
	destroy_tab((void **)argv);
	quit(0, NULL, vars);
	return (1);
}

/*
*pour comprendre la structure des if, 
*il faut aller regarder le comportement de bash
*avec "exit pout"
* "exit pout pout"
* "exit 1 pout pout"
*/
