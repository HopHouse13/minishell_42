/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/02/17 16:00:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lexer)
{
	lexer->i = -1;
	lexer->intoken = false;
}

bool	ft_isspace(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	ft_ischevron(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	ft_isnotredirection(char c)
{
	if (c != '<' || c != '>' || c != '|')
		return (true);
	return (false);
}

bool	ft_ispipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}