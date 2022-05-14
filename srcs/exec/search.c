/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:09:06 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 16:34:24 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../environment/env.h"
#include "../utils/utils.h"

static inline int	create_path(char **path, char *name)
{
	*path = ft_strdup(name);
	if (!path)
		return (-1);
	return (SLASH_SUCCESS);
}

static inline int	file_exist(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
		return (NOFILE);
	stat(path, &st);
	if (S_ISDIR(st.st_mode))
		return (ISDIR);
	return (0);
}

static inline int	return_exec(char *path)
{
	if (access(path, X_OK) == 0)
		return (SEARCH_SUCCESS);
	free(path);
	return (NOEXEC);
}

static inline int	search_in_tab(char **path, char *name, char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		*path = add_name(tab[i], name);
		if (!*path)
		{
			destroy_tab((void **)tab);
			return (-1);
		}
		if (access(*path, F_OK) == 0)
		{
			destroy_tab((void **)tab);
			return (return_exec(*path));
		}
		free(*path);
		*path = NULL;
		i++;
	}
	destroy_tab((void **)tab);
	return (SEARCH_FAIL);
}

/*
*effectue une recherche d'un executable ou d'un builtin
*-1 = une erreur est survenue
*0 = recherche de commande a raté
*1 = recherche réussie mais fichier non executable
*2 = contient des slash et path a été défini
*3 = est un builtin
*4 = recherche a réussie et path a éte défini
*/
int	search(t_vars *vars, t_cmd *cmd, char **path)
{
	char	*name;
	char	**tab;

	*path = NULL;
	name = cmd->cmd->data;
	if (has_slash(name))
	{
		if (file_exist(name))
			return (file_exist(name));
		if (access(name, X_OK) == 0)
			return (create_path(path, name));
		return (NOEXEC);
	}
	if (is_builtin(name))
		return (BUILTIN_SUCCESS);
	if (env_get("PATH", vars) == NULL)
		return (SEARCH_FAIL);
	tab = ft_split(env_get("PATH", vars), ':');
	if (!tab)
		return (-1);
	return (search_in_tab(path, name, tab));
}
/*cherche d'abord si name contient des slash,
* si oui et qu'il est executable alors path sera le nom et on return
* ensuite cherche si c'est un builtin, si oui path sera null et on return
* ensuite cherche aux différents dossiers renseignés par la variable d'env PATH
* si toujours rien trouvé alors recherche a fail
*/
