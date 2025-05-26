/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaning_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:08 by pbret             #+#    #+#             */
/*   Updated: 2025/05/26 21:42:37 by pab              ###   ########.fr       */
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

void	ft_make_clear_input(t_mshell *mshell, t_lexer *lexer, char *wild_input)
{
	bool	in_space;

	lexer->clear_input = ft_malloc_list(mshell, sizeof(char)
			* ft_count_char(wild_input) +1);
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
			lexer->clear_input[lexer->j++] = wild_input[lexer->i];
		}
		else if (wild_input[lexer->i] == ' ' && in_space == false)
		{
			in_space = true;
			lexer->clear_input[lexer->j++] = wild_input[lexer->i];
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

void	ft_cleaning_input(t_mshell *mshell, t_lexer *lexer)
{
	printf("\n\n\t--------------------- ONE_SPACE ---------------------\n");
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
	lexer->wild_input[++lexer->j] = '\0';
	ft_make_clear_input(mshell, lexer, lexer->wild_input);
	ft_printf("\n\n\tclear_line : [%s]\n\n", lexer->clear_input);
}
