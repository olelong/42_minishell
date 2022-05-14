/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:16:42 by afaure            #+#    #+#             */
/*   Updated: 2022/01/21 23:15:46 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"

int	ft_pwd(t_vars *vars, char **argv)
{
	const char	*pwd;

	(void)argv;
	pwd = env_get("PWD", vars);
	if (write(STDOUT_FILENO, pwd, ft_strlen(pwd)) == -1)
	{
		write_err(ERR_PWD, NULL, strerror(errno));
		return (FAILURE);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
