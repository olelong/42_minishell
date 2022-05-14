/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:37:33 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 23:47:31 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_minishell.h"

/*
** Signal handler function to create a new line 
** with a prompt when you press ctrl-c.
*/

void	handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_last_status = -(signum + 128);
}

void	handler_heredoc(int signum)
{
	(void)signum;
	rl_replace_line("", 1);
	rl_redisplay();
	rl_done = 1;
	g_last_status = -(signum + 128);
}
