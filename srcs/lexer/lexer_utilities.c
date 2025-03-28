/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/03/28 23:20:28 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Si c est une quote simple (') et qu'on n'est pas dans une quote double :
// On ouvre ou ferme simple_q.
// On retourne OUT_Q.

// Si c est une quote double (") et qu'on n'est pas dans une quote simple :
// On ouvre ou ferme double_q.
// On retourne OUT_Q.

// On retourne 1 si on est dans une quote (simple_q ou double_q), sinon 0.
int	ft_inside_quotes_lexer(t_lexer *lexer, char c)
{
	if (c == '\'' && lexer->double_q == OUT_Q)
	{
		if (lexer->simple_q == IN_Q)
			lexer->simple_q = OUT_Q;
		else 
			lexer->simple_q = IN_Q;
		return (OUT_Q);
	}
	if (c == '\"' && lexer->simple_q == OUT_Q)
	{
		if (lexer->double_q == IN_Q)
			lexer->double_q = OUT_Q;
		else
			lexer->double_q = IN_Q;
		return (OUT_Q);
	}
	printf("\tsimple_q: %d\tdouble_q: %d\n", lexer->simple_q, lexer->double_q);
	return (lexer->simple_q == IN_Q || lexer->double_q == IN_Q);
}

void	ft_init_line(char *virgin_line)
{
	int	i;

	i = -1;
	while (++i < SIZE_LINE)
		virgin_line[i] = '\0';
	return ;
}

bool	ft_valid_character(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (false);
	return (true);
}	