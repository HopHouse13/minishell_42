/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/04/17 18:29:36 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_len_only_one_space (char *wild_input)
{
	int		i;
	int		count_carac;
	bool	in_space;
	
	in_space = false;
	count_carac = 0;
	i = -1;
	while (wild_input[++i])
	{
		if (wild_input[i] != ' ')
		{
			in_space = false;
			count_carac++;
		}
		else if (wild_input[i] == ' ' && in_space == false)
		{
			in_space = true;
			count_carac++;
		}
	}
	return (count_carac);
}

void	ft_handle_space(t_lexer *lexer, char *wild_input, t_mnode **ml)
{
	int		len_one_space;
	int		i;
	int		j;
	bool	in_space;
	
	len_one_space = ft_len_only_one_space(wild_input);
	lexer->input_clear = ft_malloc_list(sizeof(char) * len_one_space + 1, ml);
	i = -1;
	j = 0;
	in_space = false;
	while (wild_input[++i])
	{
		if (wild_input[i] != ' ')
		{
			in_space = false;
			lexer->input_clear[j++] = wild_input[i];
		}
		else if (wild_input[i] == ' ' && in_space == false)
		{
			in_space = true;
			lexer->input_clear[j++] = wild_input[i];
		}
	}
	lexer->input_clear[j] = '\0';
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

// void	ft_put_redirection(t_lexer *lexer, char *input)
// {
// 	lexer->wild_input[++lexer->j] = ' ';
// 	if (input[lexer->i++] == '<')
// 	{
// 		lexer->wild_input[++lexer->j] = '<';
// 		if (lexer->i +1 && input[lexer->i++] == '<')
// 			lexer->wild_input[++lexer->j] = '<';
// 	}
// 	else if (input[lexer->i++] == '>')
// 	{
// 		lexer->wild_input[++lexer->j] = '>';
// 		if (lexer->i +1 && input[lexer->i++] == '>')
// 			lexer->wild_input[++lexer->j] = '>';
// 	}
// 	lexer->wild_input[++lexer->j] = ' ';
// }

void	ft_put_pipe(t_lexer *lexer)
{
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
