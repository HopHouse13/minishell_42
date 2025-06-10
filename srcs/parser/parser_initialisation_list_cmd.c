/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:48:36 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 15:31:20 by phautena         ###   ########.fr       */
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

void	ft_init_list_cmd(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	ft_add_node_cmd(mshell, parser);
	while (tmp)
	{
		if (tmp->token == PIPE)
			ft_add_node_cmd(mshell, parser);
		tmp = tmp->next;
	}
}
