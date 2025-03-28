/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/28 19:01:26 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_parser(t_mshell *mshell, t_token *list_token, t_mnode **ml)
{
	t_parser	parser;
	
	ft_init_parser(mshell, &parser, list_token);
	if (ft_valid_syntax(&parser, ml))
	{printf("\nSUCCESS\n\n");
		ft_init_list_cmd(&parser, ml);
		ft_expand_and_cleanup(&parser, ml);
		//ft_fill_list_cmd(&parser, ml);
		return (parser.list_cmd);
	}
	printf("\nFAILURE\n\n");
	return (NULL); 
	
}
