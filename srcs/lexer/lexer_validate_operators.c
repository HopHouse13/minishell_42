/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operateurs_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/03/02 17:31:55 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (++lexer->i < ft_strlen(input))
	{
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_quote == OUT_Q)
		{
			if ((input[lexer->i] == '<' || input[lexer->i] == '>') 
				&& input[lexer->i + 1])
			{
				lexer->i++;
				if (input[lexer->i] == input[lexer->i - 1])
				{
					if (input[lexer->i + 1])
						lexer->i++;
					else
						break ;	
				}
				while (input[lexer->i] == ' ')
					lexer->i++;
				if (ft_valid_carac(input[lexer->i]) == false)
					return (false);
			}
		}
	}
	return (true);
}

bool	ft_control_pipe_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (++lexer->i < ft_strlen(input))
	{	
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_quote == OUT_Q)
		{
			if (input[lexer->i] == '|' && input[lexer->i + 1])
			{
				lexer->i++;
				while (input[lexer->i] == ' ')
					lexer->i++;
				if (ft_valid_carac(input[lexer->i]) == false)
					return (false);
			}
		}
	}
	return (true);
}

bool	ft_control_carac_valid(t_lexer *lexer, char *input)
{
	char	c;

	lexer->i = -1;
	while (++lexer->i < ft_strlen(input))
	{
		c = input[lexer->i];
		ft_check_quotes(lexer, c);
		if ((c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')'
			|| c == ';' || c == '&') && lexer->flag_quote == OUT_Q)
			return (false);
	}
	return (true);
}
	
bool	ft_control_quotes_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (input[++lexer->i])
		ft_check_quotes(lexer, input[lexer->i]);
	if (lexer->flag_quote == OUT_Q)
		return (true);
	return (false);
}

bool	ft_validate_operators(t_lexer *lexer, char *input)
{
	if (ft_control_quotes_valid(lexer, input) == false)
		return (printf("false_quote\n"), false);// erreur a gerer
	if (ft_control_carac_valid(lexer, input) == false)
		return (printf("false_carac\n"), false);// erreur a gerer
	if (ft_control_pipe_valid(lexer, input) == false)
		return (printf("false_operators\n"), false);// erreur a gerer
	if (ft_control_redir_valid(lexer, input) == false)
		return (printf("false_redir\n"), false);// erreur a gerer
	return (true);
}