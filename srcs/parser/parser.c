/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/07 16:02:58 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ft_supp_quotes(t_token *tmp)
// {
// 	int	i;
// 	int	nb_quotes;

// 	i = -1;
// 	while (tmp->elem[++i])
// 		if (tmp->elem[i] == '\'')
// 		{
// 			tmp->squote = 0;
// 		}	
// 		else if (tmp->elem[i] == '\"')
// 		{
			
// 		}	
// }

// void	ft_expand(t_parser *parser)
// {
// 	t_token *tmp;
	
// 	tmp = parser->list_token;
// 	while (tmp)
// 	{
// 		if (tmp->token == ELEM && ft_is_quote(tmp))
// 			ft_supp_quotes(tmp);
// 		tmp = tmp->next;
// 	}
// }
void	ft_init_list_cmd(t_cmd **list_cmd) // a modifier
{
	t_token	*fist_node;
	
	fist_node = malloc(sizeof(t_cmd));
	if (!fist_node)
	{
		perror("initialization list ");
		//ft_master_free(list_token);
		return ;
	}
	
	fist_node->prev = NULL;
	fist_node->next = NULL;
	*list_cmd = fist_node;
}

void	ft_add_node_cmd(t_parser *parser) // a modifier
{
	t_cmd	*tmp_head;
	t_cmd	*new_elem;
	
	if (!parser->list_cmd)
	{
		ft_init_list_cmd(&(parser->list_cmd));
		return ;
	}
	new_elem = malloc(sizeof (t_cmd));
	if (!new_elem)
	{
		perror("initialization list ");
		//ft_master_free(list);
		return ;
	}
	tmp_head = parser->list_cmd;
	while (tmp_head->next != NULL)
		tmp_head = tmp_head->next;
	
	new_elem->prev = tmp_head;
	new_elem->next = NULL;
	tmp_head->next = new_elem;
}
void ft_init_list_cmd(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	ft_add_node_cmd(parser);
	while (tmp)
	{
		if (tmp->token == PIPE)
			ft_add_node_cmd(parser);
		tmp = tmp->next;
	}
}

t_cmd	*ft_parser(t_token *list_token)
{
	t_parser	parser;

	ft_init_parser(&parser, list_token);
	ft_print_list_token(parser.list_token);
	//ft_init_list_cmd(&parser);
	//ft_expand(&parser);
	
	return (NULL);
}