/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:39:26 by afaure            #+#    #+#             */
/*   Updated: 2022/01/22 18:31:00 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"
#include "builtins.h"

static int	arg_error(int i)
{
	if (i > 2)
		write_err(ERR_CD, NULL, ERR_TOO_MANY);
	if (i == 1)
		write_err(ERR_CD, NULL, ERR_NOT_ENOUGH);
	return (WRONG_USE);
}

static int	error_manager(char *temp, t_vars *vars)
{
	if (temp)
		free(temp);
	if (errno == ENOMEM)
		quit(1, ERR_CD, vars);
	else
		write_err(ERR_CD, NULL, strerror(errno));
	return (1);
}

static int	get_work_dir(char *buff)
{
	if (!getcwd(buff, BUFF_SIZE_MINISHELL))
	{
		write_err(ERR_CD, NULL, strerror(errno));
		return (0);
	}
	return (1);
}

static inline int	ft_cd_next(t_vars *vars, char *temp, char *buff)
{
	if (!getcwd(buff, BUFF_SIZE_MINISHELL))
		return (error_manager(temp, vars));
	temp = ft_strjoin("PWD=", buff);
	if (!temp)
		return (error_manager(temp, vars));
	env_set(temp, vars);
	if (env_set(temp, vars))
		return (error_manager(temp, vars));
	free(temp);
	return (SUCCESS);
}

int	ft_cd(char **argv, t_vars *vars)
{
	size_t	i;
	char	*temp;
	char	buff[BUFF_SIZE_MINISHELL];

	i = 0;
	while (argv[i])
		i++;
	if (i != 2)
		return (arg_error(i));
	if (!get_work_dir(buff))
		return (FAILURE);
	temp = ft_strjoin("OLDPWD=", buff);
	if (!temp)
		return (error_manager(temp, vars));
	if (env_set(temp, vars))
		return (error_manager(temp, vars));
	free(temp);
	temp = NULL;
	if (chdir(argv[1]) == -1)
		return (error_manager(temp, vars));
	return (ft_cd_next(vars, temp, buff));
}
