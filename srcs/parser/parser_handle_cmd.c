/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:14:40 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 15:28:38 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_no_cmd(t_cmd *current, int count_str)
{
	if (count_str == 0)
		current->no_cmd = true;
}

void	ft_make_cmd_tab(t_mshell *mshell, t_token *list_token, t_cmd *list_cmd)
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
	check_no_cmd(list_cmd, count_str);
	list_cmd->cmd = ft_malloc_list(mshell, sizeof(char *) * (count_str + 1));
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

void	ft_handle_cmd(t_mshell *mshell, t_parser *parser)
{
	t_token	*list_token;
	t_cmd	*list_cmd;

	list_token = parser->list_token;
	list_cmd = parser->list_cmd;
	ft_make_cmd_tab(mshell, list_token, list_cmd);
	while (list_token->token != END)
	{
		if (list_token->token == PIPE)
		{
			list_cmd = list_cmd->next;
			list_token = list_token->next;
			ft_make_cmd_tab(mshell, list_token, list_cmd);
		}
		else
			list_token = list_token->next;
	}
}

