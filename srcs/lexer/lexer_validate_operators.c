/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/05/12 20:47:16 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_redir_valid(t_mshell *mshell, t_lexer *lexer, char *input)
{printf("\n\n\t---------------------- REDIR ------------------------\n");
	bool	flag = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{
		if (!ft_status_qts(mshell->qts, input, lexer->i)
			&& !ft_effect_esc(mshell->qts, input, lexer->i))
		{
			if ((input[lexer->i] == '<' || input[lexer->i] == '>'))
			{
				if (flag)
					return (false);
				flag = true;
				if (input[lexer->i] == input[lexer->i + 1])
					lexer->i++;
			}
			else
				flag = false;
		}
	}
	return (true);
}

bool	ft_character_valid(t_mshell *mshell, t_lexer *lexer, char *input)
{printf("\n\n\t-------------------- CARAC_VALID --------------------\n");
	char	c;

	lexer->i = -1;
	while (input[++lexer->i])
	{
		c = input[lexer->i];
		if (!ft_status_qts(mshell->qts, input, lexer->i)
			&& !ft_effect_esc(mshell->qts, input, lexer->i))// pour eviter d'interdir n'importe quel caractere car dans des quotes ou il a le caractere d'echappement juste avant.
			if (c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')'
				|| c == ';' || c == '&' || c == '#'
				|| (lexer->i == ft_strlen(input) - 1 && c == '\\'))
				return (false);
	}
	return (true);
}

bool	ft_validate_operators(t_mshell *mshell, t_lexer *lexer, char *input)
{
	if (!ft_character_valid(mshell, lexer, input))
		return (printf("false_carac\n"), false);// erreur a gerer
	if (!ft_redir_valid(mshell, lexer, input))
		return (printf("false_redir\n"), false);// erreur a gerer
	return (true);
}