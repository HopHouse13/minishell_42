/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/02/13 14:21:55 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	lexer->tokens = NULL;
	lexer->i = -1;
}

ft_build_list_tokens(char *input, t_lexer *lexer)
{
	while(input[++(lexer->i)])
	{
		
	}
}

t_token	*ft_lexer(char *input, t_mshell mshell)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer); // a completer
	ft_build_list_tokens(input, &lexer); // a faire
	return (lexer.tokens);
}