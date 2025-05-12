/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:41:17 by pbret             #+#    #+#             */
/*   Updated: 2025/05/12 22:23:35 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_init_lexer(t_lexer *lexer)
{
	ft_init_line(lexer->wild_input);
	lexer->input_clear = NULL;
	lexer->list_token = NULL;
	lexer->i = -1;
	lexer->j = -1;
	lexer->cmd_in_pipe = false;
}
