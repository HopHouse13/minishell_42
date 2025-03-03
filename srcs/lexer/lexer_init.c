/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:41:17 by pbret             #+#    #+#             */
/*   Updated: 2025/03/03 17:52:04 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	ft_init_line(lexer->line);
	lexer->list_tokens = NULL;
	lexer->i = -1;
	lexer->j = -1;
	lexer->squote = OUT_Q;
	lexer->dquote = OUT_Q;
	lexer->flag_quote = OUT_Q;
}