/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:41:17 by pbret             #+#    #+#             */
/*   Updated: 2025/04/09 18:04:07 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	ft_init_line(lexer->line);
	lexer->list_token = NULL;
	lexer->i = -1;
	lexer->j = -1;
	lexer->simple_q = OUT;
	lexer->double_q = OUT;
	lexer->flag_q = false;
	lexer->mark_q = OUT;
	lexer->APP_HD = false;
}
