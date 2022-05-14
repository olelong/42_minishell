/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:31:43 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 19:04:34 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef  _DEFAULT_SOURCE
#  define _POSIX_C_SOURCE 199309L
#  define _DEFAULT_SOURCE
# endif 

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "defs.h"
# include "structs.h"
# include "libft.h"

# define BUFF_SIZE_MINISHELL 256

extern int	g_last_status;

#endif
