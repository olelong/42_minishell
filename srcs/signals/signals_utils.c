/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:37:53 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 19:38:32 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_minishell.h"

void	init_child_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_non_interactive_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_interactive_signal(void)
{
	struct sigaction	sa;
	struct sigaction	ign;

	ft_memset(&ign, 0, sizeof(ign));
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &ign, NULL);
}

void	init_heredoc_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
}
