/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:46:30 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:14:34 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "../../include/minishell.h"

int		redir_out(const char *path, bool append);
/*
*redirects output to file specified by path
* WARNING you have to save a copy of stdout before calling
* and reconnect stdout_fileno to stdout after this
*/
int		redir_in(const char *path);
/*
*redirects stdin to file specified by path
* WARNING you have to save a copy of stdin before calling
* and reconnect stdin_fileno to stdin after this
*/

int		do_redir(t_cmd *cmd, t_wrd *redirs);
int		do_redir_right(const char *path, int *temp, bool append);
int		do_redir_left(const char *path, int *temp);
int		undo_redir(t_cmd *cmd);

int		do_heredoc(t_vars *vars, t_cmd *cmd, t_wrd *wrd);
int		check_heredoc(t_vars *vars);
char	*create_heredoc(t_vars *vars, t_wrd **head, t_wrd *wrd);
int		read_heredoc(t_vars *vars, int fd, char *limiter);
char	*create_name(t_vars *vars);
t_wrd	*expand_limiter(t_vars *vars, t_wrd **head, t_wrd *wrd);
void	write_heredoc(int fd, t_wrd *word);
t_wrd	*expand_heredoc(t_vars *vars, t_wrd *parsed_line);
void	destroy_heredocs(t_vars *vars);

#endif
