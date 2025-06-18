/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:48:36 by pab               #+#    #+#             */
/*   Updated: 2025/06/18 21:05:12 by pbret            ###   ########.fr       */
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

void	ft_move_out_node(t_token *node)
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

// dans la direction next, ca ne supp pas le PIPE
// dans la direction prev, cela le supp (c'est bien)
// je vais devoir rajouter un PIPE si le noeud avec l'ELEM NULL est entre deux PIPE
// pour eviter de melanger les CMD
void	ft_remove_node_list_token(t_token *node)
{
	t_token	*tmp;
	t_token	*next_node;

	tmp = node->next;
	while (tmp && tmp->token != END)
	{
		next_node = tmp->next;
		if (tmp->token == PIPE)
		{
			ft_move_out_node(tmp);
			break ;
		}
		ft_move_out_node(tmp);
		tmp = next_node;
	}
	tmp = node->prev;
	while (tmp)
	{
		next_node = tmp->next;
		ft_move_out_node(tmp);
		if (tmp->token == PIPE)
			break ;
		tmp = next_node;
	}
	ft_move_out_node(node);
}

bool	ft_init_list_cmd(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;
	t_token *next;
	
	tmp = parser->list_token;
	while(tmp)
	{
		next = tmp->next;
		if (tmp->elem[0] == '\0')
		{
			if (tmp == parser->list_token)
			{
				parser->list_token = next;
				if (next)
					parser->list_token->prev = NULL;
			}
			ft_remove_node_list_token(tmp);
		}
		tmp = tmp->next;
	}
	tmp = parser->list_token;
	ft_print_list_token(parser->list_token);
	if (tmp->token == END)
		return (false); // si pas pas de node dans list_token (car supp les node juste avant) -> return (new line)
	ft_add_node_cmd(mshell, parser);
	while (tmp)
	{
		if (tmp->token == PIPE)
			ft_add_node_cmd(mshell, parser);
		tmp = tmp->next;
	}
	return (true);
}
