/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/03/27 16:47:04 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_inside_quotes_lexer(t_lexer *lexer, char c)
{
	if (c == '\'' && lexer->dquote == OUT_Q && lexer->squote == OUT_Q)
		lexer->squote = IN_Q;
	else if (c == '\'' && lexer->squote == IN_Q && lexer->dquote == OUT_Q)
		lexer->squote = OUT_Q;
	else if (c == '\"' && lexer->squote == OUT_Q && lexer->dquote == OUT_Q)
		lexer->dquote = IN_Q;
	else if (c == '\"' && lexer->dquote == IN_Q && lexer->squote == OUT_Q)
		lexer->dquote = OUT_Q;
	if ((lexer->squote == IN_Q || lexer->dquote == IN_Q) 
		&& (c != '\'' && c != '\"'))
		lexer->flag_q = IN_Q;
	else
		lexer->flag_q = OUT_Q;
	printf("S_quote : %d\tD_quote : %d\t>>> value quotes : %d\n",lexer->squote, lexer->dquote, lexer->flag_q);
	return (lexer->flag_q);
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