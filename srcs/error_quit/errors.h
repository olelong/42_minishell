/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:59:24 by afaure            #+#    #+#             */
/*   Updated: 2022/01/22 18:36:11 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "../../include/minishell.h"
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>

/*
* frees all memory and quits the program
*if print_errno = true you can put error as the prefix that should be used
*by default if env = NULL, it exists with >0 status
*/
void	quit(bool print_errno, const char *error, t_vars *env);

/*
*writes an error message like this "minishell: "prefix": "name": "error"
*only error parameter is mandatory
*/
void	write_err(const char *prefix, const char *name, const char *error);

void	write_signal(int signum);

void	cmd_error(t_vars *vars, const char *error, int exit);
void	free_all(t_vars *vars);
/*
*permet de quitter le programme
* print_errno : si il est TRUE alors le message de errno sera affiché 
* (faire ça seukement si un malloc par exemple ou une fonction de la libc fail)
* error = [une_de_nos_define] si jamais tu veux afficher un message custom
*error = 0 si jamais tu n'a rien à afficher
*/
#endif
