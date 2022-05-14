/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:38:49 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 16:44:08 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "builtins.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"

static inline void	remove_space(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		str[j] = str[i];
		if (ft_isspace(str[i]))
		{
			while (ft_isspace(str[i]))
				i++;
		}
		else
			i++;
		j++;
	}
	str[j] = '\0';
}

static inline void	set_var(char *arg, char **temp, t_vars *vars)
{
	remove_space(arg);
	if (env_set(arg, vars) == FAILURE)
	{
		destroy_tab((void **)temp);
		quit(1, ERR_EXPORT, vars);
	}
}

int	export(char **argv, t_vars *vars)
{
	int		ret;
	char	**temp;

	ret = SUCCESS;
	temp = argv;
	argv++;
	if (!*argv)
		return (print_env(vars));
	while (*argv)
	{
		if (is_valid_id(*argv))
			set_var(*argv, temp, vars);
		else
		{
			write_err(ERR_EXPORT, *argv, ERR_INVALID_ID);
			ret = FAILURE;
		}
		argv++;
	}
	return (ret);
}
