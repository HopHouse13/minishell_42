/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suppresion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:26:59 by pbret             #+#    #+#             */
/*   Updated: 2025/04/10 18:00:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 // PROBLEME le \ est aussi enleve dans les doubles quotes alors qu'il n'est pas devant " / $ 
 // faut qu'il soit supprimer uniquement devant ces 3 caracteres
char	*ft_remove_escape_char(t_parser *parser, char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_without_b;
	char	*str_without_b;
	
	i = -1;
	count_without_b = 0;
	while (str[++i])
		if (str[i] != '\\' || ft_effect_escape_parser(parser, str, i))
			count_without_b++;
	str_without_b = ft_malloc_list(sizeof(char) * count_without_b + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if  (str[i] != '\\' || ft_effect_escape_parser(parser, str, i))
			str_without_b[j++] = str[i];
	str_without_b[j] = '\0';
	return (str_without_b);
}

char	*ft_remove_quotes(t_parser *parser, char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_without_q;
	char	*str_without_q;
	
	i = -1;
	count_without_q = 0;
	while (str[++i])
		if (ft_inside_quotes_parser(parser, str, i) 
			|| ft_effect_escape_parser(parser, str, i)
			|| (str[i] != '\'' 	&& str[i] != '\"'))
			count_without_q++;
	str_without_q = ft_malloc_list(sizeof(char) * count_without_q + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if (ft_inside_quotes_parser(parser, str, i) 
			|| ft_effect_escape_parser(parser, str, i)
			|| (str[i] != '\'' 	&& str[i] != '\"'))
			str_without_q[j++] = str[i];
	str_without_q[j] = '\0';
	return (str_without_q);
}

char	*ft_suppression(t_parser *parser, char *str, t_mnode **ml)
{
	char	*result;

	result = NULL;
	result = ft_remove_quotes(parser, str, ml);
	result = ft_remove_escape_char(parser, result, ml);
	return (result);
}

void	ft_delete_quotes_and_escape_char(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_suppression(parser, tmp->elem, ml);
		tmp = tmp->next;
	}
}