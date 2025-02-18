/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/02/18 19:51:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parcer(t_parser *parser)
{
	ft_init_line(parser->line);
}

bool	ft_check_quotes_input(char *input)
{
	int	i;
	bool	squote;
	bool	dquote;
	
	i = -1;
	squote = true; // true(1) = exterieur de quote
	dquote = true; // false(0) = interieur de quote
	while (input[++i])
	{
		if (input[i] == '\'' && dquote == true && squote == true)
			squote = false;
		else if (input[i] == '\'' && squote == false && dquote == true)
			squote = true;
		else if (input[i] == '\"' && squote == true && dquote == true)
			dquote = false;
		else if (input[i] == '\"' && dquote == false && squote == true)
			dquote = true;
	}
	if (squote == true && dquote == true)
		return (true);
	return (false);
}

void	ft_parser(t_mshell *mshell, char *input)
{
	t_parser	parser;

	ft_init_parcer(&parser);
	ft_check_quotes_input(input);
	//ft_put_spaces()
/* 	int i = -1;
	while (++i < 1000)
		ft_printf("value carac line : [%c]\n", parser.line[i]); */
	(void)mshell->input;
}

// "bonjour'je'suis'" 'hello"i"am"'
// "bonjourjesuis" 'helloiam'