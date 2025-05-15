/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:41:17 by pbret             #+#    #+#             */
/*   Updated: 2025/05/15 22:51:22 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_init_lexer(t_mshell *mshell, t_lexer *lexer, t_mnode **ml)
{
	lexer->wild_input = NULL;
	ft_init_wild_input(mshell, lexer, ml);
	lexer->clear_input = NULL;
	lexer->list_token = NULL;
	lexer->i = -1;
	lexer->j = -1;
	lexer->cmd_in_pipe = false;
}
