/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/03/28 11:55:16 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_inside_quotes_lexer(t_lexer *lexer, char c)
{
	if (c == '\'' && lexer->doubleq == OUT_Q)
	{
		if (lexer->simpleq == IN_Q)
			lexer->simpleq = OUT_Q;
		else 
			lexer->simpleq = IN_Q;
		return (OUT_Q);
	}
	if (c == '\"' && lexer->simpleq == OUT_Q)
	{
		if (lexer->doubleq == IN_Q)
			lexer->doubleq = OUT_Q;
		else
			lexer->doubleq = IN_Q;
		return (OUT_Q);
	}
	printf("S_quote: %d\tD_quote: %d\n", lexer->simpleq, lexer->doubleq);
	return (lexer->simpleq == IN_Q || lexer->doubleq == IN_Q);
}

void	ft_init_line(char *virgin_line)
{
	int	i;

	i = -1;
	while (++i < SIZE_LINE)
		virgin_line[i] = '\0';
	return ;
}

bool	ft_valid_carac(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (false);
	return (true);
}	