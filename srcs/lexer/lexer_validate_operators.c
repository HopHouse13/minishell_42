/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/05/15 22:21:02 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_redir_valid(t_mshell *mshell, char *input)
{printf("\n\n\t---------------------- REDIR ------------------------\n");
	int		i;
	bool	flag = false;
	
	i = -1;
	while (input[++i])
	{
		if (!ft_status_qts(mshell->qts, input, i)
			&& !ft_effect_esc(mshell->qts, input, i))
		{
			if ((input[i] == '<' || input[i] == '>'))
			{
				if (flag)
					return (false);
				flag = true;
				if (input[i] == input[i + 1])
					i++;
			}
			else
				flag = false;
		}
	}
	return (true);
}

bool	ft_character_valid(t_mshell *mshell, char *input)
{printf("\n\n\t-------------------- CARAC_VALID --------------------\n");
	int 	i;
	char	c;

	i = -1;
	while (input[++i])
	{
		c = input[i];
		if (!ft_status_qts(mshell->qts, input, i)
			&& !ft_effect_esc(mshell->qts, input, i)
			&& (c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')'
			|| c == ';' || c == '&' || c == '#'
			|| (i == ft_strlen(input) - 1 && c == '\\')))
				return (false);
		}
	return (true);
}

bool	ft_validate_operators(t_mshell *mshell, char *input)
{
	if (!ft_character_valid(mshell, input))
		return (printf("false_carac\n"), false);// erreur a gerer
	if (!ft_redir_valid(mshell, input))
		return (printf("false_redir\n"), false);// erreur a gerer
	return (true);
}