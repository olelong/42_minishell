/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:37:40 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 00:58:36 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "../utils/utils.h"

void	free_all(t_vars *vars)
{
	if (vars->command_line)
	{
		lst_destroy_cmd(vars->command_line);
		vars->command_line = NULL;
	}
	if (vars->env)
	{
		destroy_tab((void **)vars->env);
		vars->env = NULL;
	}
	if (vars->line)
	{
		free(vars->line);
		vars->line = NULL;
	}
	if (vars->parsed_line)
	{
		lst_destroy_wrd(vars->parsed_line);
		vars->parsed_line = NULL;
	}
	clear_history();
}
