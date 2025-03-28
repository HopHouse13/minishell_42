/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:41:17 by pbret             #+#    #+#             */
/*   Updated: 2025/03/28 11:56:30 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	ft_init_line(lexer->line);
	lexer->list_token = NULL;
	lexer->i = -1;
	lexer->j = -1;
	lexer->simpleq = OUT_Q;
	lexer->doubleq = OUT_Q;
	lexer->flag_q = OUT_Q;
	lexer->APP_HD = false;
}