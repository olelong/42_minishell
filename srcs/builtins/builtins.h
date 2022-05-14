/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:37:53 by afaure            #+#    #+#             */
/*   Updated: 2022/01/21 22:53:42 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/minishell.h"

int	ft_echo(char **argv, t_vars *vars);
int	env(char **argv, t_vars *vars);
int	ft_exit(char **argv, t_vars *vars);
int	export(char **argv, t_vars *vars);
int	ft_cd(char **argv, t_vars *vars);
int	ft_pwd(t_vars *vars, char **argv);
int	unset(char **argv, t_vars *vars);

#endif
