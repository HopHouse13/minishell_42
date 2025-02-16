/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/02/16 14:55:30 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	lexer->i = -1;
}

bool	ft_isspace(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	ft_isredirection(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}