/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/04/18 19:05:29 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* bool	ft_cmds(char *cmd) // apparemment useless car organiquement execve va gerer.
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cat") || !ft_strcmp(cmd, "grep")
		|| !ft_strcmp(cmd, "wc") || !ft_strcmp(cmd, "sort")
		|| !ft_strcmp(cmd, "uniq") || !ft_strcmp(cmd, "awk")
		|| !ft_strcmp(cmd, "sed") || !ft_strcmp(cmd, "head")
		|| !ft_strcmp(cmd, "tail"))
		return (true);
	return (false);
}

char	*ft_find_next_cmd(t_token *tmp)
{
	while (tmp && tmp->token != END)
	{
		if (tmp->token == CMD)
			return (tmp->elem);
		tmp = tmp->next;
	}
	return (NULL);
} */

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet
bool	ft_effect_escape_parser(t_parser *parser, char *str, int i)
{
	bool	on_off;

	on_off = false;
	if((parser->double_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
	|| parser->simple_q)
	return (on_off);
	while (--i>= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}

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
