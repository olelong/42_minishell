/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:59:53 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 02:56:51 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "../../include/minishell.h"
#include <stdbool.h>
#include <unistd.h>

void	quit(bool print_errno, const char *error, t_vars *vars)
{
	int	ret;

	if (print_errno)
		write_err(error, NULL, strerror(errno));
	else if (error)
		write_err(false, error, NULL);
	if (vars != NULL)
	{
		if (g_last_status < 0)
			g_last_status = -g_last_status;
		ret = g_last_status;
		free_all(vars);
	}
	else
		ret = EXIT_FAILURE;
	exit(ret);
}
