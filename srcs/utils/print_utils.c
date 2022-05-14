/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaure <afaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:30:56 by afaure            #+#    #+#             */
/*   Updated: 2022/01/24 15:26:51 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

const char	*enum_to_str(t_type type)
{
	const char	*jsp_to_str[] = {"UNKOWN", "WRD", "QUOTE_IN", "QUOTE_OUT",
		"WHITESPACES", "REDIR_LEFT",
		"REDIR_HEREDOC", "REDIR_RIGHT", "REDIR_APPEND", "DOLLAR", "PIPE_"};

	return (jsp_to_str[type]);
}

void	print_wrd_list(t_wrd *head)
{
	while (head)
	{
		printf("type : %s\t\t", enum_to_str(head->type));
		printf("data : %s\n", head->data);
		head = head->next;
	}
}

static const char	*print_cmd_type(t_cmd_type type)
{
	if (type == CMD)
		return ("CMD");
	if (type == PIPE)
		return ("PIPE");
	return ("INVALID");
}

void	print_cmd_list(t_cmd *head)
{
	while (head)
	{
		printf("CMD type : %s\n", print_cmd_type(head->type));
		if (head->cmd)
			print_wrd_list(head->cmd);
		printf("PRINT actual  : %p\n", head);
		printf("PRINT next    : %p\n", head->next);
		printf("PRINT prec    : %p\n", head->prec);
		head = head->next;
	}
}
