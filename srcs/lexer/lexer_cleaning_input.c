/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/05/19 16:35:58 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_char(char *line)
{
	int		i;
	int		count;
	bool	in_space;

	i = 0;
	count = 0;
	in_space = false;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			in_space = false;
			count++;
		}
		else if (line[i] == ' ' && !in_space)
		{
			in_space = true;
			count++;
		}
		i++;
	}
	return (count);
}

void	ft_make_input(t_lexer *lexer, char *w_input, t_mshell *ms, t_mnode **ml)
{
	bool	in_space;
	
	lexer->clear_input = ft_malloc_list(sizeof(char) *
							ft_count_char(w_input) + 1, ms, ml);
	lexer->i = 0;
	lexer->j = 0;
	in_space = false;
	while (w_input[lexer->i] == ' ')
		lexer->i++;
	while (w_input[lexer->i])
	{
		if (w_input[lexer->i] != ' ')
		{
			in_space = false;
			lexer->clear_input[lexer->j++] = w_input[lexer->i];
		}
		else if (w_input[lexer->i] == ' ' && in_space == false)
		{
			in_space = true;
			lexer->clear_input[lexer->j++] = w_input[lexer->i];
		}
		lexer->i++;
	}
	lexer->clear_input[lexer->j] = '\0';
}

void	ft_put_redirection(t_lexer *lexer, char *input)
{
	if ((lexer->i > 0 && input[lexer->i -1] != input[lexer->i])
		|| (lexer->i > 1 && input[lexer->i -1] == input[lexer->i]
		&& input[lexer->i -2] == input[lexer->i]))
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

void	ft_cleaning_input(t_mshell *mshell, t_lexer *lexer, t_mnode **ml)
{printf("\n\n\t--------------------- ONE_SPACE ---------------------\n");
	lexer->i = 0;
	while (mshell->input && mshell->input[lexer->i])
	{
		if (ft_status_qts(mshell->qts, mshell->input, lexer->i)
			|| ft_effect_esc(mshell->qts, mshell->input, lexer->i))
			lexer->wild_input[++lexer->j] = mshell->input[lexer->i];
		else
		{
			if (mshell->input[lexer->i] == '|')
				ft_put_pipe(lexer);
			else if ((mshell->input[lexer->i] == '<' 
					|| mshell->input[lexer->i] == '>'))
				ft_put_redirection(lexer, mshell->input);
			else 
				lexer->wild_input[++lexer->j] = mshell->input[lexer->i];
		}
		lexer->i++;
	}
	lexer->wild_input[++lexer->j] = ' ';
	lexer->wild_input[++lexer->j] = ';';
	// lexer->wild_input[++lexer->j] = '\0'; // pas oublige car calloc mais je prefere
	ft_make_input(lexer, lexer->wild_input, mshell, ml);
	ft_print_input_clean(lexer->clear_input); // ASUPP
}
