/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:40:44 by afaure            #+#    #+#             */
/*   Updated: 2022/01/25 01:10:11 by afaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../include/minishell.h"

void		destroy_tab(void **tab);
void		remove_str_tab(char **tab, char *elem, bool do_free);
/*
** Prends une liste chainée contenant uniquement des types wrd et
** retourne un tableau de chaines de characteres
*/
char		**wrd_to_argv(t_wrd *wrd);

/*fonction qui retourne un maillon wrd*/
t_wrd		*lst_new_wrd(t_type type, char *data);
/*fonction qui retourne un mailloncmd*/
t_cmd		*lst_new_cmd(t_cmd_type type, t_wrd *cmd);
/*fonction qui ajoute un maillon cmd à la fin de la chaine*/
int			lst_add_cmd(t_cmd *ptr, t_cmd_type type, t_wrd *cmd);

/*fonction qui ajoute un maillon wrd a la fin de la chaine */
int			lst_add_wrd(t_wrd **ptr, t_type type, char *data);

/*fonction qui ajoute un maillon cmd juste apres le maillon indiqué*/
int			lst_add_after_cmd(t_cmd *ptr, t_cmd_type type, t_wrd *cmd);

/*fonction qui ajoute un maillon wrd juste apres le maillon indiqué*/
int			lst_add_after_wrd(t_wrd *ptr, t_type type, char *data);

/*detruit une liste entiere de cmd*/
void		lst_destroy_cmd(t_cmd *head);

/*detruit une liste chainee de wrd*/
void		lst_destroy_wrd(t_wrd *head);

/*retire et free un seul maillon d'une liste cmd*/
void		lst_remove_one_cmd(t_cmd **head, t_cmd *cmd);

/*retire et free un seul maillon d'une liste wrd*/
void		lst_remove_one_wrd(t_wrd **head, t_wrd *wrd);
/*free str1, alloue de la mémoire assez grande pour les deux*/
char		*ft_realloc(char *str1, const char *str2);

const char	*enum_to_str(t_type type);
void		print_wrd_list(t_wrd *head);
void		print_cmd_list(t_cmd *head);
void		print_tab(char **tab);

int			event(void);
/*
** inutile sers juste pour readline dans l'init du main
*/
#endif
