/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/04/18 18:51:25 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_space(t_lexer *lexer, char *wild_input, t_mnode **ml)
{
	bool	in_space;
	
	lexer->input_clear = ft_malloc_list(sizeof(char) *
							ft_strlen(wild_input) + 1, ml);
	lexer->i = 0;
	lexer->j = 0;
	in_space = false;
	while (wild_input[lexer->i] == ' ')
		lexer->i++;
	while (wild_input[lexer->i])
	{
		if (wild_input[lexer->i] != ' ')
		{
			in_space = false;
			lexer->input_clear[lexer->j++] = wild_input[lexer->i];
		}
		else if (wild_input[lexer->i] == ' ' && in_space == false)
		{
			in_space = true;
			lexer->input_clear[lexer->j++] = wild_input[lexer->i];
		}
		lexer->i++;
	}
	lexer->input_clear[lexer->j] = '\0';
}

void	ft_put_redirection(t_lexer *lexer, char *input)
{
	if (lexer->i > 0 && input[lexer->i -1] != input[lexer->i])
		lexer->wild_input[++lexer->j] = ' ';
	if (input[lexer->i] == '<')
	lexer->wild_input[++lexer->j] = '<';
	else if (input[lexer->i] == '>')
		lexer->wild_input[++lexer->j] = '>';
	if (input[lexer->i +1] && input[lexer->i +1] != input[lexer->i])
		lexer->wild_input[++lexer->j] = ' ';
}

void	ft_put_pipe(t_lexer *lexer)
{
	if (lexer->i != 0)
		lexer->wild_input[++lexer->j] = ' ';
	lexer->wild_input[++lexer->j] = '|';
	lexer->wild_input[++lexer->j] = ' ';
}

void	ft_input_one_space(t_lexer *lexer, char *input, t_mnode **ml)
{printf("\n\n\t----------------------INPUT------------------------\n");
	lexer->i = 0;
	while (input && lexer->i < SIZE_LINE && input[lexer->i])
	{
		if (ft_inside_quotes_lexer(lexer, input, lexer->i) || 
			ft_effect_escape_lexer(lexer, input, lexer->i))
			lexer->wild_input[++lexer->j] = input[lexer->i];
		else
		{
			if (input[lexer->i] == '|')
				ft_put_pipe(lexer);
			else if ((input[lexer->i] == '<' || input[lexer->i] == '>'))
				ft_put_redirection(lexer, input);
			else 
				lexer->wild_input[++lexer->j] = input[lexer->i];
		}
		lexer->i++;
	}
	lexer->wild_input[++lexer->j] = ' ';
	lexer->wild_input[++lexer->j] = ';';
	ft_handle_space(lexer, lexer->wild_input, ml);
	ft_print_input_clean(lexer->input_clear); // ASUPP
}
