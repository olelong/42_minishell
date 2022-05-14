/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:58:56 by olelong           #+#    #+#             */
/*   Updated: 2022/01/25 01:35:06 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../../include/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# define PROMPT "msh$ "

/*
** init_copy.c
*/

t_cmd	*init_parser(void);
char	*copy(char *str, int start, t_vars *vars);

/*
** check_op.c
*/

int		is_operator(char c);
t_type	get_type(char *str, int *quote_i);
t_type	check_quote(char c, int *quote_i);
int		quote_is_open(int quote_i, t_vars *vars);
void	add_simple_quote(t_vars *vars, t_wrd **word);

/*
** create_cmd.c
*/

void	parse_cmd(t_cmd **cmd, t_wrd **word, t_vars *vars);

/*
** empty_line.c
*/

int		is_empty(char *str, int end);

/*
** syntax_error.c
*/

int		print_syntax_error(char token, char *str);
int		syntax_error(char *str);

/*
** check_line.c
*/

void	check_single_wrd(char *str, int start, int len, t_vars *vars);
int		check_space(char *str, int i, int quote_i, t_vars *vars);
int		add_a_word(char *str, int i, int *is_double_op, t_vars *vars);

/*
** parse.c
*/

void	parser(char *str, int *quote_i, t_vars *vars);
int		parse_heredoc(char *str, t_vars *vars);
int		is_operator_a_word(char c, int quote_i);
void	add_op(t_vars *vars, char *str, int *quote_i);

#endif
