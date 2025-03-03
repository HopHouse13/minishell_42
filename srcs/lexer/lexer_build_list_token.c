/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/03/03 17:07:11 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_build_list_tokens(t_lexer *lexer)
{
	int	start;

	lexer->i = -1;
	lexer->j = 0; //len de la sous chaine
	start = 0; // debut de la sous chaine
	while (lexer->line[++lexer->i])
	{
		while (lexer->line[lexer->i] == ' ')
			lexer->i++;
		if (lexer->line[lexer->i] != ' ' && start == 0)
			start = lexer->i;
		while (lexer->line[lexer->i] != ' ')
		{
			lexer->j++;
			ft_substr(lexer->line, start, lexer->j);
		}
	}
}