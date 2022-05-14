/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:51:47 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 13:48:48 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../include/minishell.h"

int			print_env(t_vars *vars);
void		env_unset(char *name, t_vars *vars);
int			env_set(const char *name_val, t_vars *vars);
int			env_init(t_vars *vars, const char **env);
void		env_copy(char **src, char **dst);
char		**env_dup(const char **env);
const char	*env_get(char *name, t_vars *vars);
bool		is_valid_id(char *str);
#endif

/*
*Important internal shell variables
* SHLVL
* LAST_EXIT
* PWD
* ptet TERM mais jsp trop
*/
