/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:56:02 by afaure            #+#    #+#             */
/*   Updated: 2022/01/22 15:49:41 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"
#include "../signals/signals_minishell.h"
#include "../error_quit/errors.h"

void	free_arg_env_path(char **argv, char **env, char *path)
{
	if (argv)
		destroy_tab((void **)argv);
	if (env)
		destroy_tab((void **)env);
	if (path)
		free(path);
}

int	exec_builtin(t_vars *vars, char **argv)
{
	if (ft_strncmp(argv[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(argv, vars));
	if (ft_strncmp(argv[0], "env", ft_strlen("env")) == 0)
		return (env(argv, vars));
	if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(argv, vars));
	if (ft_strncmp(argv[0], "export", ft_strlen("export")) == 0)
		return (export(argv, vars));
	if (ft_strncmp(argv[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(argv, vars));
	if (ft_strncmp(argv[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(vars, argv));
	if (ft_strncmp(argv[0], "unset", ft_strlen("unset")) == 0)
		return (unset(argv, vars));
	return (1);
}

static inline size_t	lst_size(t_wrd *wrd)
{
	size_t	ret;

	ret = 0;
	while (wrd)
	{
		wrd = wrd->next;
		ret++;
	}
	return (ret);
}

/*
*prends une liste chainée contenant uniquement des types wrd 
*et retourne un tableau de chaines de characteres
*/
char	**wrd_to_argv(t_wrd *wrd)
{
	size_t	size;
	size_t	i;
	char	**tab;

	i = 0;
	size = lst_size(wrd);
	tab = ft_calloc(1, (size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (wrd)
	{
		tab[i] = ft_strdup(wrd->data);
		if (!tab[i])
		{
			destroy_tab((void **)tab);
			return (NULL);
		}
		wrd = wrd->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
