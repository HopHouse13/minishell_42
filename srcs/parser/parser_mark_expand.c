/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:25 by pbret             #+#    #+#             */
/*   Updated: 2025/04/11 13:13:20 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_insert_marker(char *str, int i, t_mnode **ml)
{
	char	*result;
	int		j;
	int		k;
	
	result = ft_malloc_list(sizeof(char) * ft_strlen(str) + 2, ml);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (k == i + 1)
			result[k++] = '!';
		else
			result[k++] = str[j++];
	}
	result[k] = '\0';
	printf("result_marker : %s\n", result);
	return (result);
}

char	*ft_marker(char *str, t_type token, t_parser *parser, t_mnode **ml)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		ft_inside_quotes_parser(parser, str, i);
		if (str[i] == '$' && parser->simple_q == OUT && token != DELIM
			&& (i == 0 || !ft_effect_escape_parser(parser, str, i)))
			str = ft_insert_marker(str, i, ml);
	}
	return (str);
}

void	ft_mark_expand(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_marker(tmp->elem, tmp->token, parser, ml);
		tmp = tmp->next;
	}
}
