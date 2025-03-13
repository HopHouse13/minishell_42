/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation_list_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:08 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/13 19:29:47 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	//init variables ici
	first_node->cmd = NULL;
	first_node->squote = -1;
	first_node->dquote = -1;	// <<<<<<<<<<<<<<<<<<<<<<<<<<< ici
	first_node->prev = NULL;
	first_node->next = NULL;
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
	//init variables ici
	new_elem->cmd = NULL;
	new_elem->squote = -1;
	new_elem->dquote = -1;			// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	new_elem->flag_hs = false;		// faire une fonciton pour init toutes les variables
	new_elem->hd_count = 0;			// meme fonction a utiliser pour  ft_inti_heas_list_cmd
	new_elem->hd = NULL;			// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	new_elem->prev = tmp;
	new_elem->next = NULL;
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
