/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_build_cmd_tab(t_token *list_token, t_cmd *list_cmd, t_mnode **ml)
{
	t_token	*start;
	int		count_str;
	int		i;	
	
	start = list_token;
	count_str = 0;
	while (start->token != PIPE && start->token != END)
	{
		if (start->token == CMD || start->token == BI || start->token == ARG)
			count_str++;
		start = start->next;
	}
	list_cmd->cmd = ft_malloc_list(sizeof(char *) * (count_str + 1), ml);
	start = list_token;
	i = 0;
	while (i < count_str)
	{
		if (start->token == CMD || start->token == BI || start->token == ARG)
			list_cmd->cmd[i++] = start->elem;
		start = start->next;
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