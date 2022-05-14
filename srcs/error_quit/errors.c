/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:05:01 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 03:00:41 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "../utils/utils.h"

void	write_signal(int signum)
{
	if (signum == 128 + SIGSEGV)
		ft_putstr_fd("Segmentation Fault (core dumped)", STDERR_FILENO);
	else if (signum == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	write_err(const char *prefix, const char *name, const char *error)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	if (name)
	{
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

//dans le cas où une erreur arrive pendant l'execution d'une commande
void	cmd_error(t_vars *vars, const char *error, int exit)
{
	if (exit >= 0)
		g_last_status = exit;
	if (error)
		write_err(ERR_MINISHELL, NULL, error);
	lst_destroy_cmd(vars->command_line);
	vars->command_line = NULL;
}
