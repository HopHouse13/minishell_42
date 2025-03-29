/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:08 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/29 18:13:36 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_node_values(t_cmd *new_elem)
{
	new_elem->cmd = NULL;
	new_elem->redir = NULL;
	new_elem->simple_q = -1;
	new_elem->double_q = -1;
	new_elem->count_hd = 0;
	new_elem->hd = NULL;
	new_elem->next = NULL;
}

void	ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml)
{
	t_cmd	*first_node;

	first_node = ft_malloc_list(sizeof(t_cmd), ml);
	if (!first_node)
	{
		perror("initialization list ");
		//ft_master_free(list_cmd);
		return ;
	}
	ft_init_node_values(first_node);
	*list_cmd = first_node;
}

void	ft_add_node_cmd(t_parser *parser, t_mnode **ml)
{
	t_cmd	*tmp;
	t_cmd	*new_elem;
	
	if (!parser->list_cmd)
		ft_init_head_list_cmd(&(parser->list_cmd), ml);
	else
	{
		new_elem = ft_malloc_list(sizeof (t_cmd), ml);
		if (!new_elem)
		{
			perror("initialization list ");
			ft_free_ml(ml);
			return ;
		}
		tmp = parser->list_cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		ft_init_node_values(new_elem);
		new_elem->prev = tmp;
		tmp->next = new_elem;
	}
}

void	ft_init_list_cmd(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;

	tmp = parser->list_token;
	ft_add_node_cmd(parser, ml);
	while (tmp)
	{
		if (tmp->token == PIPE)
		ft_add_node_cmd(parser, ml);
		tmp = tmp->next;
	}
}
