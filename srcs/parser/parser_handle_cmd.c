/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:14:40 by pab               #+#    #+#             */
/*   Updated: 2025/05/12 22:03:29 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_build_cmd_tab(t_token *list_token, t_cmd *list_cmd, t_mnode **ml)
{
	t_token	*tmp;
	int		count_str;
	int		i;
	
	tmp = list_token;
	count_str = 0;
	while (tmp->token != PIPE && tmp->token != END)
	{
		if (tmp->token == CMD || tmp->token == BI || tmp->token == ARG)
			count_str++;
		tmp = tmp->next;
	}
	list_cmd->cmd = ft_malloc_list(sizeof(char *) * (count_str + 1), ml);
	tmp = list_token;
	i = 0;
	while (i < count_str)
	{
		if (tmp->token == BI)
			list_cmd->builtin = true;
		if (tmp->token == CMD || tmp->token == BI || tmp->token == ARG)
			list_cmd->cmd[i++] = tmp->elem;
		tmp = tmp->next;
	}
	list_cmd->cmd[i] = NULL;
}

void	ft_handle_cmd(t_parser *parser, t_mnode **ml)
{
	t_token	*list_token;
	t_cmd	*list_cmd;
	
	list_token = parser->list_token;
	list_cmd = parser->list_cmd;
	ft_build_cmd_tab(list_token, list_cmd, ml);
	while (list_token->token != END)
	{
		if (list_token->token == PIPE)
		{
			list_cmd = list_cmd->next;
			list_token = list_token->next;
			ft_build_cmd_tab(list_token, list_cmd, ml);
		}
		else
			list_token = list_token->next;
	}
}
