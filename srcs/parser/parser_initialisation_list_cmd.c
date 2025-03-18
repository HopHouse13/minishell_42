/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:08 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/18 20:20:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_node_values(t_cmd *new_elem, bool first_node)
{
	if(first_node)
	{
		new_elem->cmd = NULL;
		new_elem->squote = -1;
		new_elem->dquote = -1;
		new_elem->prev = NULL;
		new_elem->next = NULL;
	}
	else
	{
		new_elem->cmd = NULL;
		new_elem->squote = -1;
		new_elem->dquote = -1;
		new_elem->hd_count = 0;
		new_elem->hd = NULL;
		new_elem->next = NULL;
	}
}

void	ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml) // a modifier
{
	t_cmd	*first_node;

	first_node = ft_malloc_list(sizeof(t_cmd), ml);
	if (!first_node)
	{
		perror("initialization list ");
		//ft_master_free(list_cmd);
		return ;
	}
	ft_init_node_values(first_node, true);
	*list_cmd = first_node;
}

void	ft_add_node_cmd(t_parser *parser, t_mnode **ml) // a modifier
{
	t_cmd	*tmp;
	t_cmd	*new_elem;
	
	if (!parser->list_cmd)
	{
		ft_init_head_list_cmd(&(parser->list_cmd), ml);
		return ;
	}
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
	ft_init_node_values(new_elem, false);
	new_elem->prev = tmp;
	tmp->next = new_elem;
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
