/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:45:04 by olelong           #+#    #+#             */
/*   Updated: 2022/01/25 01:31:38 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"
#include "../environment/env.h"
#include "../exec/exec.h"
#include "../signals/signals_minishell.h"
#include "../error_quit/errors.h"

int	g_last_status = 0;

static void	init_main(int ac, const char **av, t_vars *v, const char **envp)
{
	(void)av;
	(void)ac;
	ft_memset(v, '\0', sizeof(t_vars));
	if (!env_init(v, envp))
		quit(1, ERR_MINISHELL, v);
	init_interactive_signal();
	if (isatty(STDIN_FILENO))
		rl_event_hook = event;
	v->line = readline(PROMPT);
}

static void	check_var_line(t_vars vars)
{
	if (vars.line)
		free(vars.line);
	vars.line = NULL;
}

void	launch(t_vars *vars, int *quote_i)
{
	vars->command_line = init_parser();
	if (!vars->command_line)
		quit(1, ERR_MINISHELL, vars);
	parser(vars->line, quote_i, vars);
}

static void	quit_main(t_vars *vars)
{
	free_all(vars);
	write(STDOUT_FILENO, "exit\n", 5);
}

/*
** The command line returned by readline() is retrieved.
** As long as there is a new line to read,
** we add the line in the terminal history,
** we can search in the history,
** if the line is not empty or filled with space and there are no
** syntax errors,
** we initialize quote_i to 0 an odd number because in all cases
** quote_in are odd,
** we initialize the struct t_wrd and t_cmd,
** we parse and fill word with tokens of type
** depending on the operators or WRD,
** we check the case where in the end there is an open quote which
** is a syntax error.
** Otherwise, if there are no syntax errors, we can parse
** the words to make them into
** commands separated by PIPE to NULL.
** We free the line once recovered and used to go to the next one.
*/

int	main(int argc, const char **argv, const char **envp)
{
	t_vars	vars;
	int		quote_i;

	init_main(argc, argv, &vars, envp);
	while (vars.line)
	{
		add_history(vars.line);
		if (vars.line && !is_empty(vars.line, -1)
			&& !syntax_error(vars.line))
		{
			quote_i = 0;
			launch(&vars, &quote_i);
			if (quote_i % 2 == 1)
				quote_is_open(quote_i, &vars);
			else
			{
				parse_cmd(&vars.command_line, &vars.command_line->cmd, &vars);
				exec_line(&vars);
			}
		}
		check_var_line(vars);
		vars.line = readline(PROMPT);
	}
	quit_main(&vars);
	return (g_last_status);
}
