/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:47:22 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 17:57:09 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../include/minishell.h"

/****************************************************\
*				CMD_EXPANSION						*
\****************************************************/

t_cmd	*expand_cmd(t_cmd *cmd, t_vars *vars);
void	cleanup_cmd(t_wrd **head);

/****************************************************\
*				WRD_EXPANSION						*
\****************************************************/
t_wrd	*parse_var(t_vars *vars, t_wrd *wrd);
t_wrd	*cleanup_wrd(t_vars *vars, t_wrd **head, t_wrd *start, t_wrd *end);
t_wrd	*expand_wrd(t_vars *vars, t_wrd **head, t_wrd *wrd);
t_wrd	*add_redirs(t_vars *vars, t_cmd *cmd, t_wrd *redir, t_wrd *name);
t_wrd	*expand_parameter(t_vars *vars, t_wrd **head, t_wrd *wrd);
t_wrd	*remove_quotes(t_vars *vars, t_wrd **head, t_wrd *wrd);
bool	valid_token(t_wrd *wrd);

#endif
