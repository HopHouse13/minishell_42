/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/27 17:02:24 by pab              ###   ########.fr       */
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

// void	ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml) // a modifier
// {
// 	t_cmd	*first_node;

// 	first_node = ft_malloc_list(sizeof(t_cmd), ml);
// 	if (!first_node)
// 	{
// 		perror("initialization list ");
// 		//ft_master_free(list_cmd);
// 		return ;
// 	}
// 	//init variables ici
// 	first_node->cmd = NULL;
// 	first_node->squote = -1;
// 	first_node->dquote = -1;
// 	first_node->prev = NULL;
// 	first_node->next = NULL;
// 	*list_cmd = first_node;
// }

// void	ft_add_node_cmd(t_parser *parser, t_mnode **ml) // a modifier
// {
// 	t_cmd	*tmp;
// 	t_cmd	*new_elem;
	
// 	if (!parser->list_cmd)
// 	{
// 		ft_init_head_list_cmd(&(parser->list_cmd), ml);
// 		return ;
// 	}
// 	new_elem = ft_malloc_list(sizeof (t_cmd), ml);
// 	if (!new_elem)
// 	{
// 		perror("initialization list ");
// 		//ft_master_free(list);
// 		return ;
// 	}
// 	tmp = parser->list_cmd;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	//init variables ici
// 	new_elem->cmd = NULL;
// 	new_elem->squote = -1;
// 	new_elem->dquote = -1;
// 	new_elem->prev = tmp;
// 	new_elem->next = NULL;
// 	tmp->next = new_elem;
// }

// void	ft_init_list_cmd(t_parser *parser, t_mnode **ml)
// {
// 	t_token	*tmp;

// 	tmp = parser->list_token;`
// 	ft_add_node_cmd(parser, ml);
// 	while (tmp)
// 	{
// 		if (tmp->token == PIPE)
// 		ft_add_node_cmd(parser, ml);
// 		tmp = tmp->next;
// 	}
// }

// 3 CHOSES A FAIRE:
// - implementer le [#] ignore tout ce qui est apres.
// - 


t_cmd	*ft_parser(t_token *list_token, t_mnode **ml)
{
	t_parser	parser;
	
	ft_init_parser(&parser, list_token);
	if (ft_valid_syntax(&parser, ml))
	{ printf("\nSUCCESS\n\n");
		ft_init_list_cmd(&parser, ml);
		//ft_expand(&parser, ml);
		//ft_fill_list_cmd(&parser, ml);
		return (parser.list_cmd);
	}
	printf("\nFAILURE\n\n");
	return (NULL); 
	
}
