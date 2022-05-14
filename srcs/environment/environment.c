/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:55:34 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 21:08:43 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../utils/utils.h"

int	env_init(t_vars *vars, const char **env)
{
	while (env[vars->env_size])
		vars->env_size++;
	vars->env = env_dup(env);
	if (!vars->env)
		return (0);
	return (1);
}

/*
*fonction utilisée par env_set, ne surtout pas appeler seule
*elle malloc un tableau plus grand pour env et ajoute la nouvelle variable
*/
static int	env_add(const char *name_val, t_vars *vars)
{
	char	**temp;

	if (!name_val)
		return (0);
	vars->env_size++;
	temp = vars->env;
	vars->env = malloc((vars->env_size + 1) * sizeof(char *));
	if (!vars->env)
	{
		destroy_tab((void **)temp);
		return (1);
	}
	env_copy(temp, vars->env);
	free(temp);
	vars->env[vars->env_size - 1] = ft_strdup(name_val);
	vars->env[vars->env_size] = NULL;
	if (!vars->env[vars->env_size - 1])
		return (1);
	return (0);
}

/*
*prends en entrée une string au format "name=value"
*et modifie la valeur de la variable si elle existe, sinon l'ajoute
* ( le while degeu sers à chercher parmis toute les entree de env 
*si une string avec le mm nom existe
* la variablke name_size permet de savoir le nbr de char que fait le nom
* avant le charactère '='
*/
int	env_set(const char *name_val, t_vars *vars)
{
	size_t	i;
	size_t	name_size;

	name_size = 0;
	i = 0;
	if (!name_val)
		return (0);
	while (name_val[name_size] && name_val[name_size] != '=')
		name_size++;
	while (vars->env[i] && ft_strncmp(name_val, vars->env[i], name_size) != 0)
		i++;
	if (vars->env[i])
	{
		free(vars->env[i]);
		vars->env[i] = ft_strdup(name_val);
		if (!vars->env[i])
			return (1);
	}
	else
		return (env_add(name_val, vars));
	return (0);
}

/*
*supprime une variable [name] de l'env
*
*cherche d'abord si la variable existe et ensuite 
*décale toute les variables en dessous d'un cran
*y compris le pointeur NULL
*et décremente env_size
*pour ne pas avoir à malloc
*/
void	env_unset(char *name, t_vars *vars)
{
	size_t	i;
	size_t	name_size;

	i = 0;
	if (!name)
		return ;
	name_size = ft_strlen(name);
	while (vars->env[i] && ft_strncmp(name, vars->env[i], name_size) != 0)
		i++;
	if (i == vars->env_size)
		return ;
	free(vars->env[i]);
	while (i < vars->env_size)
	{
		vars->env[i] = vars->env[i + 1];
		i++;
	}
	vars->env_size--;
}

/*
*retourne un pointeur sur la valeur associée à name
*NULL si la variable n'existse pas ou n'a rien d'assigné
* (d'ou la verification qu'il ya des chars après name)
*/
const char	*env_get(char *name, t_vars *vars)
{
	size_t	i;
	size_t	name_size;

	i = 0;
	if (!name)
		return (NULL);
	name_size = ft_strlen(name);
	while (vars->env[i] && ft_strncmp(name, vars->env[i], name_size + 1)
		!= '\0' - '=')
		i++;
	if (vars->env[i])
		return (&vars->env[i][name_size + 1]);
	return (NULL);
}
/*
*parcours le tableau d'env, si il trouve une variable name qui correspond
* le truc chelou avec la comparaison entre le \0 et = 
*c'est pour etre sur qu'il y a un = derrire le name
*/
