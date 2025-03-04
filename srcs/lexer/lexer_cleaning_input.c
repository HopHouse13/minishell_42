/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/03/04 17:18:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_put_redirection(t_lexer *lexer, char *input)
{
	if (lexer->i != 0 && input[lexer->i - 1] != ' ')
		lexer->line[++lexer->j] = ' ';
	if (input[lexer->i] == '<')
	{
		lexer->line[++lexer->j] = input[lexer->i];
		if (lexer->i + 1 && input[lexer->i + 1] == '<')
			lexer->line[++lexer->j] = input[++lexer->i];
	}
	else if (input[lexer->i] == '>')
	{
		lexer->line[++lexer->j] = input[lexer->i];
		if (lexer->i + 1 && input[lexer->i + 1] == '>')
			lexer->line[++lexer->j] = input[++lexer->i];
	}
	if (lexer->i + 1 < ft_strlen(input) && input[lexer->i + 1] != ' ')
		lexer->line[++lexer->j] = ' ';
}
void	ft_put_pipe(t_lexer *lexer, char *input)
{
	if (lexer->i != 0 && input[lexer->i - 1] != ' ')
		ft_handle_space(lexer, input);
	lexer->line[++lexer->j] = '|';
	if (lexer->i + 1 < ft_strlen(input) && input[lexer->i + 1] != ' ')
		ft_handle_space(lexer, input);
}

void	ft_input_one_space(t_lexer *lexer, char *input)
{
	lexer->i = 0;
	while (input && lexer->i < SIZE_LINE && input[lexer->i])
	{
		ft_check_quotes(lexer, input[lexer->i]);
		if (lexer->flag_quote == OUT_Q)
		{
			if (input[lexer->i] == '|')
				ft_put_pipe(lexer, input);
			else if ((input[lexer->i] == '<' || input[lexer->i] == '>'))
				ft_put_redirection(lexer, input);
			else if (input[lexer->i] == ' ')
				ft_handle_space(lexer, input);
			else
				lexer->line[++lexer->j] = input[lexer->i];
		}
		else
			lexer->line[++lexer->j] = input[lexer->i];
		lexer->i++;
	}
	ft_printf("\nline : [%s]\n\n", lexer->line); // ASUPP
}
