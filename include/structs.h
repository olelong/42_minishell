/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:43:50 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 23:08:59 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd	t_cmd;
typedef struct s_wrd	t_wrd;

typedef enum e_type
{
	UNKNOWN,
	WRD,
	QUOTE_IN,
	QUOTE_OUT,
	WHITESPACES,
	REDIR_LEFT,
	REDIR_HEREDOC,
	REDIR_RIGHT,
	REDIR_APPEND,
	DOLLAR,
	PIPE_
}				t_type;

typedef enum e_cmd_type
{
	CMD,
	PIPE
}				t_cmd_type;

typedef enum e_status
{
	CLEAR,
	IN_QUOTE,
	IN_DBL_QUOTES
}				t_status;

typedef struct s_exec
{
	int		temp_stdin;
	int		temp_stdout;
	int		pip[2];
	pid_t	pid;
	bool	in_pipe;

	t_cmd	*left_child;
	t_cmd	*right_child;
}				t_exec;

typedef struct s_wrd
{
	t_type	type;
	char	*data;

	t_wrd	*next;
	t_wrd	*prec;
}				t_wrd;

typedef struct s_cmd
{
	t_cmd_type	type;

	t_wrd		*cmd;
	t_wrd		*redirs;

	t_exec		exec;
	t_cmd		*next;
	t_cmd		*prec;
}			t_cmd;

typedef struct s_vars
{
	char	*line;
	t_cmd	*command_line;
	char	**env;
	size_t	env_size;

	int		heredoc_counter;
	t_wrd	*parsed_line;
}			t_vars;

#endif
