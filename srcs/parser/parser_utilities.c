/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/03/26 02:56:02 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_cmds(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cat") || !ft_strcmp(cmd, "grep") || !ft_strcmp(cmd, "wc") || !ft_strcmp(cmd, "sort")
		|| !ft_strcmp(cmd, "uniq") || !ft_strcmp(cmd, "awk") || !ft_strcmp(cmd, "sed") || !ft_strcmp(cmd, "head")
		|| !ft_strcmp(cmd, "tail"))
		return (true);
	return (false);
}
char	*ft_find_next_cmd(t_token *tmp)
{
	while (tmp && tmp->token != END)
	{
		if (tmp->token == CMD)
			return (tmp->elem);
		tmp = tmp->next;
	}
	return (NULL);
}