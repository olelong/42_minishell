/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:39:28 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:15:27 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"
#include "../signals/signals_minishell.h"
#include "../error_quit/errors.h"
#include "../environment/env.h"
#include "../redir/redir.h"
#include "../expansion/expansion.h"

/*lors de l'exec d'une command
*1) effectuer toutes lres redirections
*                     effectuer la recherche
*2) si c'est un builtin executer le builtins
*3) si il n'y a pas de / dans le nom, chercher dans path un executable de ce nom
*4) si la recherche echoue, return avec un status 127
*3) si il y a un / dans le nom, ou si la recherche a réussi executer la commande
*
*                   executer la commande/le builtin
*4)dans le cas de l'execution d'un builtin, j'appelle simplement la fonction
*5)dans le cas de l'execution d'un autre programme, 
        si je ne suis pas dans un pipe, 
			je dois fork puis executer le programme 
			et attendre la fin de son execution
        si je suis dans un pipe, je dois simplement executer le programme
        dans le cas d'une erreur d'execution
			je renvoie juste une erreur et je ne quitte pas
6) je dois défaire les redirections à la fin
*/

static inline int	error_return(int error, t_cmd *cmd, t_vars *vars)
{
	if (error == -1)
		quit(1, ERR_MINISHELL, vars);
	if (error == ISDIR)
	{
		write_err(ERR_MINISHELL, cmd->cmd->data, ERR_ISDIR);
		return (127);
	}
	if (error == NOFILE)
	{
		write_err(ERR_MINISHELL, cmd->cmd->data, strerror(errno));
		return (127);
	}
	if (error == SEARCH_FAIL)
	{
		write_err(ERR_MINISHELL, cmd->cmd->data, ERR_NO_CMD);
		return (127);
	}
	else if (error == NOEXEC)
	{
		write_err(ERR_MINISHELL, cmd->cmd->data, strerror(errno));
		return (126);
	}
	return (1);
}

static inline void	free_quit(char **argv, char **env, char *path, t_vars *vars)
{
	free_arg_env_path(argv, env, path);
	quit(1, ERR_MINISHELL, vars);
}

/*effectue les redirections puis une recherche d'un executable ou d'un builtin
*retourne le résultat de l'execution dans le cas 
*d'un builtin ou d'une simple commande non pipee */
int	search_exec_command(t_vars *vars, t_cmd *cmd, bool in_pipe)
{
	int		ret;
	char	*path;
	char	**argv;

	cmd = expand_cmd(cmd, vars);
	if (do_redir(cmd, cmd->redirs) == FAILURE)
		return (1);
	if (!cmd->cmd)
		return (undo_redir(cmd));
	ret = search(vars, cmd, &path);
	if (ret < BUILTIN_SUCCESS)
		return (error_return(ret, cmd, vars));
	argv = wrd_to_argv(cmd->cmd);
	if (!argv)
		free_quit(argv, NULL, path, vars);
	if (ret == BUILTIN_SUCCESS)
		ret = exec_builtin(vars, argv);
	else if (ret == SLASH_SUCCESS || ret == SEARCH_SUCCESS)
		ret = exec_command(argv, path, vars, in_pipe);
	free_arg_env_path(argv, NULL, path);
	if (undo_redir(cmd) == 1)
		return (1);
	return (ret);
}
/* ligne 73 commande trouvée mais non executable 
* 	OU commande ou fichier introuvable OU une erreur est survenue
* Ligne 78 la commande est un builtin
* Ligne 80 contient des slash ou une commande est trouvée, path est défini
*/

int	exec_command(char **argv, char *path, t_vars *vars, bool in_pipe)
{
	char	**env;
	int		ret;

	ret = 0;
	env = env_dup((const char **)vars->env);
	if (!env)
		free_quit(argv, env, path, vars);
	if (in_pipe == false)
		ret = exec_with_fork(path, argv, env, vars);
	else
		exec_without_fork(path, argv, env, vars);
	destroy_tab((void **)env);
	return (ret);
}

/*Ligne 99/ 101, un test pour savoir si on est dans un pipe
* si on est pas dans un pipe on doit executer 
*la commande dans un environement forké
* si on est dans un pipe, on est déja dans un fork
*/
