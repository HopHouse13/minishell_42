/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:16:51 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 21:19:24 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_inval(t_mshell *ms, char *str, char *ev_exp, t_parser *parser)
{
	char	*before;
	char	*after;
	char	*middle;
	char	*str_merge;

	str_merge = NULL;
	before = ft_substr_ml(ms, str, 0, parser->srt -2);
	after = ft_substr_ml(ms, str, parser->end +1, ft_strlen(str));
	if (ev_exp[0] == '\"' || ev_exp[0] == '\'')
		str_merge = ft_strjoin_ml(ms, before, ft_strjoin_ml(ms, "", after));
	else if (ev_exp[0] == '\\')
		str_merge = ft_strjoin_ml(ms, before, ft_strjoin_ml(ms, "$", after));
	else
	{
		middle = ft_strjoin_ml(ms, "$", ev_exp);
		str_merge = ft_strjoin_ml(ms, before, ft_strjoin_ml(ms, middle, after));
	}
	return (str_merge);
}

char	*ft_merge(t_mshell *ms, char *str, char *ev_exp, t_parser *parser)
{
	char	*before;
	char	*after;
	char	*str_merge;

	if (!ft_isalpha(str[parser->srt]) && str[parser->srt] != '_'
		&& str[parser->srt] != '?')
		str_merge = ft_inval(ms, str, ev_exp, parser);
	else
	{	
		before = ft_substr_ml(ms, str, 0, parser->srt -2); // -2 car on veut une len et pas un indexe donc +1 pour passer d'un indexe a une len ET comme [start] = 'H' $[HOME]; [start-3] = carac devant $ DONC -3 + 1 = -2
		after = ft_substr_ml(ms, str, parser->end +1, ft_strlen(str));
		str_merge = ft_strjoin_ml(ms, before, ft_strjoin_ml(ms, ev_exp, after));
	}
	return (str_merge);
}

char	*ft_expand(t_mshell *mshell, char *elem, t_parser *parser)
{
	char	*ev_name;
	char	*ev_ptr;
	char	*ev_expanded;

	parser->srt = parser->i +2; // pour arriver a la 1er carac du nom. ex : $[HOME] i = $ ; i+2 = H
	if (elem[parser->srt] == '?')
	{
		parser->end = parser->srt +1;
		return (ft_itoa_ml(mshell, g_exit_code));
	}
	ev_name = ft_get_ev_name(mshell, elem, parser);
	if (!ev_name)
	{
		parser->end = parser->srt +1;
		return (ft_substr_ml(mshell, elem, parser->srt, 1));
	}
	printf("\tVAR_NAME : %s\n", ev_name);
	ev_ptr = ft_found_value_key(mshell, ev_name);
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(mshell, ev_ptr);
	else
		ev_expanded = ft_strdup_ml(mshell, "");
	return (ev_expanded);
}

void	ft_exp_elem(t_mshell *mshell, t_token *tmp, t_parser *parser)
{
	char	*ev_exp;

	parser->i = -1;
	while (tmp->elem[++parser->i])
	{
		if (tmp->elem[parser->i] == '$' && tmp->elem[parser->i +1] == '[')
		{
			ev_exp = ft_expand(mshell, tmp->elem, parser);
			printf("\tEXPANDED : %s\n", ev_exp); // ASUPP
			tmp->elem = ft_merge(mshell, tmp->elem, ev_exp, parser);
			parser->i = -1;
		}
	}
}

void	ft_expand_list(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		ft_exp_elem(mshell, tmp, parser);
		printf("\tELEM_FINAL : %s\n", tmp->elem); // ASUPP
		tmp = tmp->next;
	}
}
