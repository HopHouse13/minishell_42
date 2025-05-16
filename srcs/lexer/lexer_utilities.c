/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/05/16 19:45:12 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_character_valid(t_mshell *mshell, char *input, t_mnode **ml)
{
	printf("\n\n\t-------------------- CARAC_VALID --------------------\n");
	int i;
	char c;

	i = -1;
	while (input[++i])
	{
		c = input[i];
		if (!ft_status_qts(mshell->qts, input, i)
		&& !ft_effect_esc(mshell->qts, input, i)
		&& (ft_invalid_character(c)
		|| (i == ft_strlen(input) - 1 && c == '\\')))
		{
			ft_err("erreur de syntaxe près du symbole inattendu", &c, 258, ml);
			return (false);
		}
	}
	return (true);
}

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

bool	ft_invalid_character(char c)
{
	if (c == '{' || c == '}' || c == '[' || c == ']' || c == '('
		|| c == ')' || c == ';' || c == '&' || c == '#')
		return (true);
	return (false);
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