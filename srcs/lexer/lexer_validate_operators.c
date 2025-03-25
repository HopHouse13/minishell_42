/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/03/25 02:51:06 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{
	bool	flag;

	flag = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_REDIR -> %c\n", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_quote == OUT_Q)
		{
			if (input[lexer->i] == '<' && input[lexer->i + 1] && input[lexer->i + 1] == '<')
				flag = true;
			else if (input[lexer->i] == '>' && input[lexer->i + 1] && input[lexer->i + 1] == '>')
				flag = true;
			if (flag == true)
				while (input[lexer->i++] == ' ')
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
	printf("-------------------REDIR---------------------\n\n");
	return (true);
} */

bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_REDIR -> %c\n", input[lexer->i]);
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
	printf("-------------------REDIR---------------------\n\n");
	return (true);
}

bool	ft_control_pipe_valid(t_lexer *lexer, char *input)
{
	bool	pipe;

	pipe = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_PIPE -> %c\t\t", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (input[lexer->i] != ' ' && ft_valid_carac(input[lexer->i]) == true) // sinon il retombe sur un 2eme pipe consecutif et il mets le bool "pipe" a zero avant de check si ct pas un 2eme pipe consecutif.
			pipe = false;
		if (lexer->flag_quote == OUT_Q)
		{
			if (input[lexer->i] == '|' && pipe == false)
				pipe = true;
			else if (pipe == true && ft_valid_carac(input[lexer->i]) == false)
				return (false);
		}
		printf("value_pipe : %d\n", pipe);
	}
	printf("-------------------PIPE---------------------\n\n");
	return (true);
}

bool	ft_control_carac_valid(t_lexer *lexer, char *input)
{
	char	c;

	lexer->i = -1;
	while (input[++lexer->i])
	{
		c = input[lexer->i];
		ft_check_quotes(lexer, c);
		if ((c == '{' || c == '}' || c == '[' || c == ']' || c == '(' ||
			c == ')' || c == ';' || c == '&') && lexer->flag_quote == OUT_Q)
			return (false);
	}
	printf("--------------------CARAC_VALID--------------------\n\n");
	return (true);
}
	
bool	ft_control_quotes_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (input[++lexer->i])
		ft_check_quotes(lexer, input[lexer->i]);
	printf("------------------QUOTES----------------------\n\n");
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