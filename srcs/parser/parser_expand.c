/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:16:51 by pab               #+#    #+#             */
/*   Updated: 2025/04/11 20:53:26 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge(char *str, char *exp, int i, t_parser *parser, t_mnode **ml)
{
	int		len_before;
	int		len_after;
	char	**tab;
	char	*str_merged;
	
	str_merged = NULL;
	len_before = 0;
	while (--i != 0)
		len_before++;
	len_after = 0;
	i = ++parser->end;
	while (i > 0 && str[i++])
		len_after++;
	printf("\tBEFORE : %d \tEXP : %d\t AFTER : %d\n\n", len_before, ft_strlen(exp), len_after); //ASUPP
	str_merged = ft_malloc_list((len_before + ft_strlen(exp) + len_after + 1)
								* sizeof(char), ml);
	tab = ft_malloc_list(sizeof(char *) * 3, ml);
	tab[0] = ft_substr_ml(str, 0, len_before, ml);
	tab[1] = ft_strdup_ml(exp, ml);
	tab[2] = ft_substr_ml(str, parser->end, len_after, ml);
	printf("\ttab0 [%s]\ttab1 [%s]\ttab2 [%s]\n\n", tab[0], tab[1], tab[2]); //ASUPP
	str_merged = ft_strjoin_ml(tab[0], ft_strjoin_ml(tab[1], tab[2], ml), ml);
	return (str_merged);
}

char	*ft_expand(char *elem, int i, t_parser *parser, t_mnode **ml)
{
	char	*var_name;
	char	*value_ptr;
	char	*var_expanded;
	
	parser->start = ++i;
	printf("\nVALUE CARAC debut : %c\n\n", elem[i]);
	if (elem[i] == '?')
	{
		parser->end = i + 1;
		// 	return (ft_itoa_ml(exit_status)); // dernier exit status
	}
	if (!ft_isalpha(elem[i]) && elem[i] != '_')
	{
		parser->end = i + 1;
		return ("");
	}
	while (elem[i] != '!')
		i++;
	parser->end = i;
	printf("\nVALUE CARAC FIN : %c\n\n", elem[i]);
	var_name = ft_substr_ml(elem, parser->start, i - parser->start, ml); // si me malloc fail c'est deja gerer dans la fonction
	printf("\n\tVAR_NAME : %s\n\n", var_name);
	value_ptr = getenv(var_name); // voir comment gerer les variables d'env car je pense qu'il y a double actuellement
	if (value_ptr)
		var_expanded = ft_strdup_ml(value_ptr, ml);
	else
		var_expanded = ft_strdup_ml("", ml);
	return (var_expanded);
}

void	ft_expand_elem(t_token *tmp, t_parser *parser, t_mnode **ml)
{
	int		i;
	char	*var_exp;
	
	i = -1;
	while (tmp->elem[++i])
	{
		ft_inside_quotes_parser(parser, tmp->elem, i);
		if (tmp->elem[i] == '!' && parser->simple_q == OUT
			&& tmp->token != DELIM && tmp->elem[i - 1] == '$'
			&& (i == 1 || !ft_effect_escape_parser(parser, tmp->elem, i)))
		{//printf("\ncarac du i : %c\n\n", tmp->elem[i]);
			parser->start = i;
			var_exp = ft_expand(tmp->elem, i, parser, ml);
			if (!var_exp)
			{
				dprintf(2, "\nINVALID_NAME_EXPAND");
				return ;
			}
			printf("\n\tExppanded : %s\n\n", var_exp);
			tmp->elem = ft_merge(tmp->elem, var_exp, i, parser, ml);
			i = -1;
		}
	}
}

void	ft_expand_list(t_parser *parser, t_mnode **ml)
{
	t_token *tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		ft_expand_elem(tmp, parser, ml);
		printf("\n\n\tELEM_FINAL : %s\n\n", tmp->elem); // ASUPP
		tmp = tmp->next;
	}
}

