/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/04/01 01:38:20 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_space(t_lexer *lexer, char *input)
{
	int	z;
	
	z = ft_strlen(input) - 1;
	while (input[z] == ' ' && z > 0)
		z--;
	if (lexer->i > 0 && lexer->i <= z)
		lexer->line[++lexer->j] = ' ';
	while (input[lexer->i + 1] == ' ')
		lexer->i++;
}

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
{printf("\n\n\t----------------------INPUT------------------------\n");
	lexer->i = 0;
	while (input && lexer->i < SIZE_LINE && input[lexer->i])
	{
		if ((lexer->i > 0 && input[lexer->i - 1] == '\\')
			|| ft_inside_quotes_lexer(lexer, input[lexer->i]))
			lexer->line[++lexer->j] = input[lexer->i];
		else
		{
			if (input[lexer->i] == '|')
			{
				ft_put_pipe(lexer, input);
			}
			else if ((input[lexer->i] == '<' || input[lexer->i] == '>'))
				ft_put_redirection(lexer, input);
			else if (input[lexer->i] == ' ')
				ft_handle_space(lexer, input);
			else
				lexer->line[++lexer->j] = input[lexer->i];
		}
		lexer->i++;
	}
	lexer->line[++lexer->j] = ' ';
	lexer->line[++lexer->j] = ';';
	ft_print_input_clean(lexer->line); // ASUPP
}


// < infile grep 'o'|wc -l>outfile
