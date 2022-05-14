/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:49:42 by afaure            #+#    #+#             */
/*   Updated: 2022/01/22 18:35:05 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"

int	unset(char **argv, t_vars *vars)
{
	int		ret;

	ret = SUCCESS;
	argv++;
	while (*argv)
	{
		if (!is_valid_id(*argv))
		{
			write_err(ERR_UNSET, *argv, ERR_INVALID_ID);
			ret = FAILURE;
		}
		else if (env_get(*argv, vars))
			env_unset(*argv, vars);
		argv++;
	}
	return (ret);
}
