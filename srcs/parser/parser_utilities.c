/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/05/12 22:08:31 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet

bool	ft_inside_brackets(t_parser *parser, char *str, int i)
{
	if (i == 0 )
		parser->mark_b = OUT;
	if (str[i] == '[' && parser->mark_b == OUT)
		parser->mark_b = IN;
	if (str[i] == ']' && parser->mark_b == IN)
		parser->mark_b = OUT;
	return (parser->mark_b);
}

int	ft_count_pipe(t_parser *parser)
{
	t_token	*tmp;
	int		count_pipe;

	count_pipe = 0;
	tmp = parser->list_token;
	while (tmp->token != END)
	{
		if ( tmp->token == PIPE)
			count_pipe++;
		tmp = tmp->next;
	}
	return (count_pipe);
}
