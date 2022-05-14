/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:56:58 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 02:54:07 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "exec.h"
#include "../redir/redir.h"
#include "../signals/signals_minishell.h"
//ICI, la fonction qui sera appellée par le parsing pour traiter la command line

//execute la ligne de commande, 
//retourne le retour de la commande ( seulement les 8 derniers bits)
void	exec_line(t_vars *vars)
{
	int	ret;

	init_exec(vars);
	init_non_interactive_signal();
	if (!check_heredoc(vars))
	{
		if (g_last_status > 0)
			g_last_status = 0;
		else
			g_last_status = -g_last_status;
		destroy_heredocs(vars);
		lst_destroy_cmd(vars->command_line);
		vars->command_line = NULL;
		return ;
	}
	ret = exec_tree(vars, get_tree_head(vars->command_line), STDIN_FILENO);
	if (vars->command_line->exec.in_pipe == true)
		wait_all(&ret, vars->command_line);
	destroy_heredocs(vars);
	lst_destroy_cmd(vars->command_line);
	vars->command_line = NULL;
	g_last_status = ret;
	init_interactive_signal();
}
