/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/03/25 16:37:00 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{printf("\n\n-------------------REDIR---------------------\n");
	lexer->i = -1;
	while (input[++lexer->i])
	{
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_q == IN_Q)
			continue ;
		if ((input[lexer->i] == '<' || input[lexer->i] == '>')
			&& (lexer->APP_HD == false && input[lexer->i + 1]
			&& input[lexer->i] == input[lexer->i + 1])) // si on vient de trouver une chevron et que c'est le 1er et que le prochain carac est le meme chevron 
			lexer->APP_HD = true;
		else if (lexer->APP_HD == true && input[lexer->i] == ' ') // si on a deja trouve un chevron et que le carac est une espace
			continue ;
		else if (lexer->APP_HD == true && input[lexer->i] != input[lexer->i -1]) // si on a deja trouve un chevron et que le carac precedent est le meme chevron (c'est pour passer au carac suivant dans les cas << ou >>)
		{
			if (ft_valid_carac(input[lexer->i]) == false)
				return (false);
			lexer->APP_HD = false;
		}
	}
	return (true);
}

/* bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_REDIR -> %c\t", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_q == IN_Q)
			continue ;
		if (input[lexer->i] == '<' || input[lexer->i] == '>')
		{
			if (input[lexer->i + 1] && input[lexer->i] == input[lexer->i + 1])
				lexer->i++;
			if (input[lexer->i + 1])
				lexer->i++;
			ft_check_quotes(lexer, input[lexer->i]);
			if (lexer->flag_q == IN_Q)
				continue ;
			while (input[lexer->i] == ' ')
				lexer->i++;
			ft_check_quotes(lexer, input[lexer->i]);
			if (lexer->flag_q == OUT_Q && !ft_valid_carac(input[lexer->i]))
				return (false);
		}
	}
	printf("-------------------REDIR---------------------\n\n");
	return (true);
} */

/* bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_REDIR -> %c\n", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_q == OUT_Q)
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
} */
bool	ft_control_pipe_valid(t_lexer *lexer, char *input)
{printf("\n\n-------------------PIPE---------------------\n");
	bool	pipe;

	pipe = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_PIPE -> %c\t", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_q) // si on se trouve dans des quotes, tu ignores la suite de la boucle et tu passes au cycle suivant
			continue;
		if (input[lexer->i] != ' ' && ft_valid_carac(input[lexer->i])) // si tu rencontres autre chose qu'un espace et que c'est pas un invalide_carac(notament un pipe) -> reset pipe
			pipe = false;
		else if (input[lexer->i] == '|' && pipe == false) // si tu rencontres un pipe et qu c'est un pipe non consecutif
			pipe = true;
		else if (pipe == true && !ft_valid_carac(input[lexer->i])) // si t'as deja croise un pipe et que tu rencontres un invalide_carac(pipe notament)
			return (false);
	}
	return (true);
}

/* bool	ft_control_pipe_valid(t_lexer *lexer, char *input)
{
	bool	pipe;

	pipe = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{printf("carac_PIPE -> %c\t\t", input[lexer->i]);
		ft_check_quotes(lexer, input[lexer->i]);
		if (input[lexer->i] != ' ' && ft_valid_carac(input[lexer->i]) == true) // sinon il retombe sur un 2eme pipe consecutif et il mets le bool "pipe" a zero avant de check si ct pas un 2eme pipe consecutif.
			pipe = false;
		if (lexer->flag_q == OUT_Q)
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
} */

bool	ft_control_carac_valid(t_lexer *lexer, char *input)
{printf("\n\n--------------------CARAC_VALID--------------------\n");
	char	c;

	lexer->i = -1;
	while (input[++lexer->i])
	{
		c = input[lexer->i];
		ft_check_quotes(lexer, c);
		if ((c == '{' || c == '}' || c == '[' || c == ']' || c == '(' ||
			c == ')' || c == ';' || c == '&') && lexer->flag_q == OUT_Q)
			return (false);
	}
	return (true);
}
	
bool	ft_control_quotes_valid(t_lexer *lexer, char *input)
{printf("\n\n------------------QUOTES----------------------\n");
	lexer->i = -1;
	while (input[++lexer->i])
		ft_check_quotes(lexer, input[lexer->i]);
	if (lexer->flag_q == OUT_Q)
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