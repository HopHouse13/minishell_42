/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_elem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:26:59 by pbret             #+#    #+#             */
/*   Updated: 2025/04/13 18:00:49 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_char_saved(t_parser *parser, char *str, int i)
{
	if (ft_inside_brackets(parser, str, i))
		return (true);
	if ( str[i] == '\\')
	{
		if (parser->simple_q)
			return (true);
		if (ft_effect_escape_parser(parser, str , i))
			return (true);
		if (parser->double_q)
		{
			if (str[i + 1] == '\\' || str[i + 1] == '$' || str[i + 1] == '\"')
				return (false);
			else
				return (true);
		}
		return (false);
	}
	else if (str[i] == '\'' || str[i] == '\"')
	{
		if (parser->mark_q || ft_effect_escape_parser(parser, str ,i))
			return (true);
		else
			return (false);
	}
	return(true);
}

// PROBLEME le \ est aussi enleve dans les doubles quotes alors qu'il n'est pas devant " / $ 
// faut qu'il soit supprimer uniquement devant ces 3 caracteres dans des doubles.
char	*ft_remove_escape_char(t_parser *parser, char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_save;
	char	*str_clear;
	
	i = -1;
	count_save = 0;
	while (str[++i])
	{
		ft_inside_quotes_parser(parser, str, i);
		if (ft_char_saved(parser, str, i))
			count_save++;
	}
	str_clear = ft_malloc_list(sizeof(char) * count_save + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
	{
		ft_inside_quotes_parser(parser, str, i);
		if (ft_char_saved(parser, str, i))
			str_clear[j++] = str[i];
	}
	str_clear[j] = '\0';
	return (str_clear);
}

void	ft_clear_escape_char_and_quotes(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_remove_escape_char(parser,  tmp->elem, ml);
		tmp = tmp->next;
	}
}
