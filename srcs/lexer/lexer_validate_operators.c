/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:15:24 by pbret             #+#    #+#             */
/*   Updated: 2025/04/01 01:37:32 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_control_redir_valid(t_lexer *lexer, char *input)
{printf("\n\n\t----------------------REDIR------------------------\n");
	lexer->i = -1;
	while (input[++lexer->i])
	{
		if ((lexer->i > 0 && input[lexer->i - 1] == '\\') || 
			ft_inside_quotes_lexer(lexer, input[lexer->i]))
			continue ;
		if ((input[lexer->i] == '<' || input[lexer->i] == '>')
			&& (lexer->APP_HD == false && input[lexer->i + 1]
			&& input[lexer->i] == input[lexer->i + 1])) // si on vient de trouver une chevron et que c'est le 1er et que le prochain carac est le meme chevron 
			lexer->APP_HD = true;
		else if (lexer->APP_HD == true && input[lexer->i] == ' ') // si on a deja trouve un chevron et que le carac est une espace
			continue ;
		else if (lexer->APP_HD == true && input[lexer->i] != input[lexer->i -1]) // si on a deja trouve un chevron et que le carac precedent est le meme chevron (c'est pour passer au carac suivant dans les cas << ou >>)
		{
			if (ft_valid_character(input[lexer->i]) == false)
				return (false);
			lexer->APP_HD = false;
		}
	}
	return (true);
}

bool	ft_control_pipe_valid(t_lexer *lexer, char *input)
{printf("\n\n\t-----------------------PIPE------------------------\n");
	bool	pipe;

	pipe = false;
	lexer->i = -1;
	while (input[++lexer->i])
	{
		if ((lexer->i > 0 && input[lexer->i - 1] == '\\')
			|| ft_inside_quotes_lexer(lexer, input[lexer->i])) // si on se trouve dans des quotes, tu ignores la suite de la boucle et tu passes au cycle suivant
			continue;
		if (input[lexer->i] != ' ' && ft_valid_character(input[lexer->i])) // si tu rencontres autre chose qu'un espace et que c'est pas un invalide_carac(notament un pipe) -> reset pipe
			pipe = false;
		else if (input[lexer->i] == '|' && pipe == false) // si tu rencontres un pipe et qu c'est un pipe non consecutif
			pipe = true;
		else if (pipe == true && !ft_valid_character(input[lexer->i])) // si t'as deja croise un pipe et que tu rencontres un invalide_carac(pipe notament)
			return (false);
	}
	return (true);
}

bool	ft_control_character_valid(t_lexer *lexer, char *input)
{printf("\n\n\t--------------------CARAC_VALID--------------------\n");
	char	c;

	lexer->i = -1;
	while (input[++lexer->i])
	{
		c = input[lexer->i];
		if ((lexer->i > 0 && input[lexer->i - 1] == '\\')
			|| ft_inside_quotes_lexer(lexer, c)) // pour eviter d'interdir n'importe quel caractere car il a le caractere d'echappement juste avant.
			continue ;
		if (lexer->i == ft_strlen(input) - 1 && c == '\\') // pour interdir '\' au dernier caractere car dans le vrai bash il est fait pour ecrire ta commande sur plusieurs lignes. (pas a gerer dans minishell)
			return (false);
		if (c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')'
			|| c == ';' || c == '&' || c == '#')
			return (false);
	}
	return (true);
}
	
bool	ft_control_quotes_valid(t_lexer *lexer, char *input)
{printf("\n\n\t--------------------QUOTES-------------------------\n");
	lexer->i = -1;
	while (input[++lexer->i])
	{
		if (lexer->i > 0 && input[lexer->i - 1] == '\\')
			continue ;
		ft_inside_quotes_lexer(lexer, input[lexer->i]);
	}
	if (lexer->simple_q == IN_Q || lexer->double_q == IN_Q)
		return (false);
	return (true);
}

bool	ft_validate_operators(t_lexer *lexer, char *input)
{
	if (ft_control_quotes_valid(lexer, input) == false)
		return (printf("false_quote\n"), false);// erreur a gerer
	if (ft_control_character_valid(lexer, input) == false)
		return (printf("false_carac\n"), false);// erreur a gerer
	if (ft_control_pipe_valid(lexer, input) == false)
		return (printf("false_operators\n"), false);// erreur a gerer
	if (ft_control_redir_valid(lexer, input) == false)
		return (printf("false_redir\n"), false);// erreur a gerer
	return (true);
}