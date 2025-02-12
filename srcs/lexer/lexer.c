/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/02/12 20:27:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_lexer(char *input, t_mshell mshell)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer); // a faire
	ft_build_list_tokens(input, &lexer); // a faire
	return (lexer.tokens);
}