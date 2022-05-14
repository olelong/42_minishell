/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:22:17 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 15:04:09 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../error_quit/errors.h"

static inline int	flag(char **argv, bool *newline)
{
	size_t	i;

	i = 1;
	argv++;
	if (*argv && ft_strncmp(*argv, "-n", 2) == 0)
	{
		while ((*argv)[i] == 'n')
			i++;
		if ((*argv)[i] != '\0')
			return (1);
		*newline = false;
		return (2);
	}
	return (1);
}

int	ft_echo(char **argv, t_vars *vars)
{
	size_t	len;
	bool	newline;

	(void)vars;
	newline = true;
	argv += flag(argv, &newline);
	while (*argv)
	{
		len = ft_strlen(*argv);
		if (argv[1])
			(*argv)[len++] = ' ';
		if (write(STDOUT_FILENO, *argv, len) == -1)
		{
			write_err(ERR_ECHO, NULL, strerror(errno));
			return (FAILURE);
		}
		argv++;
	}
	if (newline && write(STDOUT_FILENO, "\n", 1) == -1)
	{
		write_err(ERR_ECHO, NULL, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
*incrémentation pour ne pas write echo ( la première string de argv)
*test pour savoir si il ya le paramtre -n
*iteration sur chacune des strings de argv pour les write 
	et les séparer par un espace
*si il y a une autre string derrière alors 
	on rajoute un espace et on augmente la len
*si je dois mettre le newline à la fin je le rajoute
* NOTE : tout les apels à write sont protegés
*/
