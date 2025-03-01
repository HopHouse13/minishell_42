/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/03/01 21:46:08 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_parser *parser)
{
	parser->i = -1;
	parser->intoken = false;
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

/// a trier ///
// validation ordre operateurs

// " <, <<, >, >>, |, ||, &&"
/* bool	ft_operators_valid(t_parser *parser, char *input)
{
	char	c;

	parser->i = 0;
	while (input[parser->i])
	{
		c = input[parser->i];
		ft_check_quotes(parser, input[parser->i]);
		{
		if ((c == '<' || c == '>') && (parser->flag_quote = OUT_Q))
			if (ft_redirection_valid(parser, input, c) == false)
				return (false);
		}
		else if ((c == '|' || c == '&') && (parser->flag_quote = OUT_Q))
		{
			if (ft_control_pipe_valid(parser, input, c) == false) // "|""&"
				return (false);
		}
		parser->i++;
	}
	return (true);
}

bool	ft_redirection_valid(t_parser *parser,char *input, char c)
{
	int	k;

	k = parser->i + 1;
	while (input[++k] == ' ')
	{

		if (input[k] == input[parser->i])
			return (false);
	}
	return (true);
} */