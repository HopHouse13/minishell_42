/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/03/01 17:53:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_quotes(t_lexer *lexer, char c)
{
	if (c == '\'' && lexer->dquote == OUT_Q && lexer->squote == OUT_Q)
		lexer->squote = IN_Q;
	else if (c == '\'' && lexer->squote == IN_Q && lexer->dquote == OUT_Q)
		lexer->squote = OUT_Q;
	else if (c == '\"' && lexer->squote == OUT_Q && lexer->dquote == OUT_Q)
		lexer->dquote = IN_Q;
	else if (c == '\"' && lexer->dquote == IN_Q && lexer->squote == OUT_Q)
		lexer->dquote = OUT_Q;
	if (lexer->squote == OUT_Q && lexer->dquote == OUT_Q)
		lexer->flag_quote = OUT_Q;
	else
		lexer->flag_quote = IN_Q;
}

void	ft_init_line(char *virgin_line)
{
	int	i;

	i = -1;
	while (++i < SIZE_LINE)
		virgin_line[i] = '\0';
	return ;
}

void	ft_handle_space(t_lexer *lexer, char *input)
{
	lexer->line[++lexer->j] = ' ';
	while (input[lexer->i + 1] == ' ')
		lexer->i++;
}

bool	ft_valid_carac(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (false);
	return (true);
}