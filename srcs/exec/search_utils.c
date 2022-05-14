/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:44:37 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 18:02:43 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//return true si la string contient un char '/'
bool	has_slash(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

//transforme une string avec "*/quelquechose" en : "quelquechose"
void	ft_remove_slash(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	i++;
	ft_memmove(str, str + i, ft_strlen(str + i));
}
//trouver le dernier char /
//deplacer i apres le /
//puis recopier la fin de str au début

//fonction qui rajoute name a la fin de path, 
//avec un slash entre les deux (path/name)
char	*add_name(const char *path, const char *name)
{
	char	*temp;
	size_t	total_size;

	total_size = ft_strlen(path) + ft_strlen(name) + 2;
	temp = malloc((total_size) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, path, total_size);
	temp[ft_strlen(path)] = '/';
	temp[ft_strlen(path) + 1] = '\0';
	ft_strlcat(temp, name, total_size);
	return (temp);
}
// Ligne 52 + 2 pour le slash et le \0

bool	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		return (true);
	if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		return (true);
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		return (true);
	if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		return (true);
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		return (true);
	if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		return (true);
	if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		return (true);
	return (false);
}
