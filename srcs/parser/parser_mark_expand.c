/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:25 by pbret             #+#    #+#             */
/*   Updated: 2025/04/11 20:29:33 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_def_var_name(char *str, int i)
{
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i + 1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i + 1);
}

char	*ft_insert_marker(char *str, int i, t_mnode **ml)
{
	char	*result;
	int		j;
	int		k;
	int		end_name;
	
	end_name = 0;
	end_name = ft_def_var_name(str, i);
	result = ft_calloc_list(ft_strlen(str) + 3, sizeof(char), ml);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (k == i)
			result[k++] = '!';
		result[k++] = str[j++];
		if (k == end_name)
			result[k++] = '!';
	}
	printf("\n\tresult_marker : %s\n\n", result);
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
			str = ft_insert_marker(str, ++i, ml);
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
