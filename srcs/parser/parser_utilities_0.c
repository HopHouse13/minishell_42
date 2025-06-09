/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 20:45:38 by pab              ###   ########.fr       */
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
	if (i == 0)
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
		if (tmp->token == PIPE)
			count_pipe++;
		tmp = tmp->next;
	}
	return (count_pipe);
}

bool	ft_srch_quotes(char *elem)
{
	int	i;

	i = -1;
	while (elem[++i])
	{
		if (elem[i] == '\'' || elem[i] == '\"')
			return (false);
	}
	return (true);
}

char	*ft_get_ev_name(t_mshell *mshell, char *elem, t_parser *parser)
{
	if (!ft_isalpha(elem[parser->srt]) && elem[parser->srt] != '_')
	{
		parser->end = parser->srt +1;
		return (NULL);
	}
	parser->end = parser->srt;
	while (elem[parser->end] && elem[parser->end] != ']')
		parser->end++;
	return (ft_substr_ml(mshell, elem, parser->srt, parser->end - parser->srt)); // end(carac : ']') - start = l'indexe du dernier carac et commme nous voulons une len -> +1 ; c'est pour ca que decrmente end apres cette ligne.
}

bool	ft_effect_escape_hd(char *str, int i)
{
	bool	on_off;

	on_off = false;
	while (--i >= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}

