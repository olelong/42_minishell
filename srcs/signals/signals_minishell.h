/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:35:02 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 19:38:41 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_MINISHELL_H
# define SIGNALS_MINISHELL_H

# include "../../include/minishell.h"

void	init_child_signal(void);
void	init_non_interactive_signal(void);
void	init_interactive_signal(void);
void	init_heredoc_signal(void);
void	handler(int signum);
void	handler_heredoc(int signum);

#endif
