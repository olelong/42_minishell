/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:38:49 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 19:41:16 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../include/minishell.h"

/*****************************************************************\
*						UTILS									 *
\*****************************************************************/
void	init_exec(t_vars *vars);
void	close_pipe(int pype[2]);

void	wait_all(int *ret, t_cmd *cmd);
void	wait_child(pid_t pid, int *ret, bool print_signal);

/*****************************************************************\
*				SINGLE COMMAND SEARCH AND EXEC					 *
\*****************************************************************/

int		search_exec_command(t_vars *vars, t_cmd *cmd, bool in_pipe);
int		exec_command(char **argv, char *path, t_vars *vars, bool in_pipe);
void	free_arg_env_path(char **argv, char **env, char *path);
int		exec_builtin(t_vars *vars, char **argv);
int		exec_with_fork(char *path, char **argv, char **env, t_vars *vars);
void	exec_without_fork(char *path, char **argv, char **env, t_vars *vars);

/*******************************************************************\
 *              COMAND LINE AND BINARY TREE EXECUTION              *
 \******************************************************************/
void	exec_line(t_vars *vars);
int		exec_tree(t_vars *vars, t_cmd *head, int stdin);
int		exec_pipe(t_vars *vars, t_cmd *head, int fd_stdin);
int		exec_left_child(t_vars *vars, t_cmd *cmd, int pype[2], int stdin);
int		exec_last_cmd(t_vars *vars, t_cmd *cmd, int stdin);
t_cmd	*get_tree_head(t_cmd *cmd);
int		create_tree(t_vars *vars);

/*****************************************************************\
*						SEARCH									 *
\*****************************************************************/

# define SEARCH_FAIL 0
# define ISDIR 1
# define NOEXEC 2
# define NOFILE 3
# define BUILTIN_SUCCESS 4
# define SLASH_SUCCESS 5
# define SEARCH_SUCCESS 6

int		search(t_vars *vars, t_cmd *cmd, char **path);
bool	has_slash(char *str);
bool	is_builtin(char *str);
void	ft_remove_slash(char *str);
char	*add_name(const char *path, const char *name);

#endif
/*
*1) prendre en compte redirections et enlever des mots
*2) expansions
*3) effectuer les redirections
*   PHASE D'EXEC/SEARCH
*4) si il n'y a pas de / dans le nom de la cmd 
	alors je cherche si c'est un builtin
 	si c'est un builtin je l'invoque
*5) si il n'y a pas de / dans le nom de la cmd 
	et que ce n'est pas un builtin
	alors je cherche dans les multiples PATH pour un fichier de ce nom
    si la recherche rate, return avec une erreur 127
*6) si la recherche a russie ou si le nom contient 
	un / alors j'execute le fichier
*/
