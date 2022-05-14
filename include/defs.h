/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:31:26 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 22:16:13 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define SUCCESS 0
# define FAILURE 1
# define WRONG_USE 2

/*		NOMS DES BUILTINS
# define BUILTIN_ECHO 0
# define BUILTIN_CD 1
# define BUILTIN_PWD 2
# define BUILTIN_EXPORT 3
# define BUILTIN_UNSET 4
# define BUILTIN_ENV 5
# define BUILTIN_EXIT 6

	TYPE DU MAILLON
# define BUILTIN	0
# define EXEC		1
# define PIPE		3
# define REDIRECT	4*/

/*					ERRORS					*/
# define ERR_MINISHELL			"minishell: "
# define ERR_INVALID_ARG		"invalid argument"
# define ERR_NO_CMD				"command not found"
# define ERR_TOO_MANY			"too many arguments"
# define ERR_NOT_ENOUGH			"not enough arguments"
# define ERR_NOT_NUMERIC		"numeric argument required"
# define ERR_INVALID_ID			"not a valid identifier"
# define ERR_NOFILE				"No such file or directory"
# define ERR_ISDIR				"Is a directory"
# define ERR_AMBIGUOUS			"ambiguous redirect"
# define ERR_EOF			"warning: here-document delimited by end-of-file"

/*	REDIRECTION	*/
# define ERR_REDIR				"minishell: redirection: "
/*	EXPANSION */
# define ERR_EXPAND				"minishell: expansion: "
/*	CD */
# define ERR_CD					"minishell: cd: "
/*	PWD	*/
# define ERR_PWD 				"minishell: pwd: "
/*	EXIT	*/
# define ERR_EXIT				"minishell: exit: "
/*	EXPORT	*/
# define ERR_EXPORT				"minishell: export: "
/*	UNSET	*/
# define ERR_UNSET				"minishell: unset: "
/*	ECHO	*/
# define ERR_ECHO				"minishell: echo: "
/*	ENV		*/
# define ERR_ENV				"minishell: env: "

#endif
