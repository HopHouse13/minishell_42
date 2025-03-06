/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/06 18:29:40 by pbret            ###   ########.fr       */
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

void ft_init_list_cmd(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp)
	{
		
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