/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:16:51 by pab               #+#    #+#             */
/*   Updated: 2025/04/07 19:21:03 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge(char *str, char *exp, int i, t_parser *parser, t_mnode **ml)
{
	int		len_dollar;
	int		len_before;
	int		len_after;
	char	**tab;
	char	*str_merged;
	
	str_merged = NULL;
	len_dollar = (parser->end - parser->start) + 1;
	len_before = 0;
	while (i-- != 0)
		len_before++;
	len_after = ft_strlen(str) - len_before - len_dollar;
	str_merged = ft_calloc_list(len_before + ft_strlen(exp) + len_after + 1, sizeof(char), ml);
	if (!str_merged)
		return (NULL); // ou renvoyer l'input sans l'expand ??
	tab = ft_malloc_list(sizeof(char *) * 3, ml);
	if (!tab)
		return (NULL); // je ne sais pas comment gerer
	tab[0] = ft_substr_ml(str, 0, len_before, ml);
	tab[1] = ft_strdup_ml(exp, ml);
	tab[2] = ft_substr_ml(str, parser->end, len_after, ml);
	printf("\ttab0 [%s]\ttab1 [%s]\ttab2 [%s]\n\n", tab[0], tab[1], tab[2]);
	str_merged = ft_strjoin_ml(tab[0], ft_strjoin_ml(tab[1], tab[2], ml), ml);
	return (str_merged);
}

char	*ft_add_brack(char *str, t_mnode **ml)
{
	return (ft_strjoin_ml(ft_strjoin_ml("[", str, ml), "]", ml));
}

char	*ft_expand(char *elem, int i, t_parser *parser, t_mnode **ml)
{
	char	*var_name;
	char	*value_ptr;
	char	*var_expanded;
	
	parser->start = ++i;
	/* if (elem[(*i)] == '?') // dernier exit status
		return (ft_itoa_ml(exit_status)); */
	if (elem[i] == '$') // PID du processus en cours
		return (ft_itoa(getpid()));
	if (!ft_isalpha(elem[i]) && elem[i] != '_')
		return (NULL);
	while (ft_isalnum(elem[i]) || elem[i] == '_')
		i++;
	parser->end = i;
	var_name = ft_substr_ml(elem, parser->start, i - parser->start, ml);
	if (!var_name)
		return (NULL);
	value_ptr = getenv(var_name);
	if (value_ptr)
		var_expanded = ft_strdup_ml(value_ptr, ml);
	else
		var_expanded = ft_strdup_ml("", ml);
	return (var_expanded);
}
// split + Join
// dup + join
void	ft_expand_list(t_parser *parser, t_mnode **ml)
{
	int		i;
	t_token *tmp;
	char	*var_exp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		i = -1;
		while (tmp->elem[++i])
		{
			/* if(i , ) */
			ft_inside_quotes_parser(parser, tmp->elem, i);
			if (tmp->elem[i] == '$' && parser->simple_q == OUT_Q
				&& tmp->token != DELIM
				&& (i == 0 || !ft_effect_escape_parser(parser, tmp->elem, i)))
			{
				parser->start = i;
				var_exp = ft_add_brack(ft_expand(tmp->elem, i, parser, ml), ml);
				printf("\n\tExppanded : %s\n\n", var_exp);
				printf("\tResult merging : %s\n\n", ft_merge(tmp->elem, var_exp, i, parser, ml));
			}
		}
		tmp = tmp->next;
	}
}
