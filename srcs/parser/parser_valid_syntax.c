/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:43 by pab               #+#    #+#             */
/*   Updated: 2025/03/24 18:26:56 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    ft_valid_syntax(t_token *list_token)
{
	t_token *tmp;
	bool	cmd;
	
	cmd = false;
	tmp = list_token;
	while (tmp->token != END)
	{
		if (tmp->token == CMD && cmd == true)
		{
			fprintf(stderr,"minishell: syntax error near unexpected token %s\n", tmp->elem);
			// exit code ?
			return (false);
		}
		if (tmp->token == CMD && cmd == false)
			cmd = true;
		if (tmp->token == PIPE)
			cmd = false;
		tmp = tmp->next;
	}
	return (true);
}
