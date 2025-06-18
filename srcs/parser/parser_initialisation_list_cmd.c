/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:48:36 by pab               #+#    #+#             */
/*   Updated: 2025/06/18 17:59:18 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_node_values(t_cmd *new_elem)
{
	new_elem->cmd = NULL;
	new_elem->path = NULL;
	new_elem->builtin = false;
	new_elem->fd_in = -1;
	new_elem->fd_out = -1;
	new_elem->fd_hd = -1;
	new_elem->delim_hd = NULL;
	new_elem->expand_hd = false;
	new_elem->no_cmd = false;
	new_elem->pid = -1;
	new_elem->prev = NULL;
	new_elem->next = NULL;
}

void	ft_init_head_list_cmd(t_mshell *mshell, t_cmd **list_cmd)
{
	t_cmd	*first_node;

	first_node = ft_malloc_list(mshell, sizeof(t_cmd));
	ft_init_node_values(first_node);
	*list_cmd = first_node;
}

void	ft_add_node_cmd(t_mshell *mshell, t_parser *parser)
{
	t_cmd	*tmp;
	t_cmd	*new_elem;

	if (!parser->list_cmd)
		ft_init_head_list_cmd(mshell, &(parser->list_cmd));
	else
	{
		new_elem = ft_malloc_list(mshell, sizeof (t_cmd));
		tmp = parser->list_cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		ft_init_node_values(new_elem);
		new_elem->prev = tmp;
		tmp->next = new_elem;
	}
}
void	ft_free_one_token_list(t_token *node)
{
	if (node->prev)
	{
		if (node->next)
			node->prev->next = node->next;	
		else
			node->prev->next = NULL;
	}
	if (node->next)
	{
		if (node->prev)
			node->next->prev = node->prev;
		else
			node->next->prev = NULL;
	}
}

void	ft_remove_node_list_token(t_token *node)
{
	while (node && node->token != PIPE)
	{
		ft_free_one_token_list(node);
		node = node->next;
	}
	while (node && node->token != PIPE)
	{
		ft_free_one_token_list(node);
		node = node->prev;
	}
}

void	ft_init_list_cmd(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while(tmp)
	{
		if (tmp->elem[0] == '\0')
			ft_remove_node_list_token(tmp);
		tmp = tmp->next;
	}
	tmp = parser->list_token;
	if () // si pas pas de node dans list_token (car supp les node juste avant) -> return (new line)
	ft_add_node_cmd(mshell, parser);
	while (tmp)
	{
		if (tmp->token == PIPE)
			ft_add_node_cmd(mshell, parser);
		tmp = tmp->next;
	}
}
