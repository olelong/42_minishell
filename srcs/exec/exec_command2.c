/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:42:42 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 14:25:37 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"
#include "../signals/signals_minishell.h"
#include "../error_quit/errors.h"

static void	exec_child_fork(char *path, char **argv, char **env, t_vars *vars)
{
	init_child_signal();
	free_all(vars);
	execve(path, argv, env);
	destroy_tab((void **)argv);
	destroy_tab((void **)env);
	free(path);
	quit(1, ERR_MINISHELL, vars);
}

int	exec_with_fork(char *path, char **argv, char **env, t_vars *vars)
{
	pid_t	child;
	int		ret;

	ret = 0;
	child = fork();
	if (child == 0)
		exec_child_fork(path, argv, env, vars);
	else if (child > 0)
		wait_child(child, &ret, 1);
	else
		ret = 1;
	return (ret);
}

/*essaye d'exec le programme, en cas d'erreur quitte*/
void	exec_without_fork(char *path, char **argv, char **env, t_vars *vars)
{
	execve(path, argv, env);
	destroy_tab((void **)argv);
	destroy_tab((void **)env);
	free(path);
	quit(1, ERR_MINISHELL, vars);
}
