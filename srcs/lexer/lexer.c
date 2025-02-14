/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/02/14 17:32:21 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



/* ft_build_list_tokens(char *input, t_lexer *lexer)
{
	while(input[++(lexer->i)])
	{
		if(!ft_isspace(input[lexer->i]))
			lexer->i++;
		else if ()
	}
} */

void	ft_lexer(t_mshell mshell, char *input)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer); // a completer ay fur et a mesure
	ft_build_list_tokens(input, &lexer); // a faire
	return (lexer.tokens);
}