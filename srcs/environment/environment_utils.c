/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:37:45 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 13:57:08 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../utils/utils.h"
#include "../error_quit/errors.h"

bool	is_valid_id(char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_' )
			return (false);
		str++;
	}
	return (true);
}

void	env_copy(char **src, char **dst)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = NULL;
}

char	**env_dup(const char **env)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (env[size])
		size++;
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
		{
			destroy_tab((void **)ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	print_env(t_vars *vars)
{
	size_t	i;
	size_t	ret;

	i = 0;
	while (vars->env[i])
	{
		ret = write(STDOUT_FILENO, vars->env[i], ft_strlen(vars->env[i]));
		ret += write(STDOUT_FILENO, "\n", 1);
		if (ret < ft_strlen(vars->env[i]))
		{
			write_err(ERR_ENV, NULL, strerror(errno));
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
