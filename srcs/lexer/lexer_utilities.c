/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/05/15 22:44:10 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_wild_input(t_mshell *mshell, t_lexer *lexer, t_mnode **ml)
{
	int	i;
	int count;
	
	i = 0;
	count = 0 ;
	while (mshell->input && mshell->input[i])
	{
		if (ft_status_qts(mshell->qts, mshell->input, i)
			|| ft_effect_esc(mshell->qts, mshell->input, i))
			count++;
		else
		{
			if (mshell->input[i] == '|')
				count = count +3;
			else if ((mshell->input[i] == '<' || mshell->input[i] == '>'))
				count = count +3;
			else 
				count++;
		}
		i++;
	}
	count = count +3; // le space + ';' + '\0' rajoute a la fin de whild_input
	lexer->wild_input = ft_calloc_list(count, sizeof (char), ml);
}

bool	ft_valid_character(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (false);
	return (true);
}

t_type	ft_builtin_or_cmd( t_lexer *lexer, char *elem)
{
	lexer->cmd_in_pipe = true;
	if (!ft_strcmp(elem, "echo") || !ft_strcmp(elem, "cd")
		|| !ft_strcmp(elem, "pwd") || !ft_strcmp(elem, "export")
		|| !ft_strcmp(elem, "unset") || !ft_strcmp(elem, "env")
		|| !ft_strcmp(elem, "exit"))
		return (BI);
	return (CMD);
}