/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:34:49 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 13:56:12 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../error_quit/errors.h"
#include"../environment/env.h"

int	env(char **argv, t_vars *vars)
{
	size_t			i;

	i = 0;
	if (argv[1])
	{
		write_err(ERR_ENV, NULL, ERR_TOO_MANY);
		return (WRONG_USE);
	}
	return (print_env(vars));
}
