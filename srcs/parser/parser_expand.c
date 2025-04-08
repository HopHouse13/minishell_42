/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:16:51 by pab               #+#    #+#             */
/*   Updated: 2025/04/08 14:37:54 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_replace_expanded_elem(char *exp, t_token *tmp, t_mnode **ml)
{
	t_token *new;
	
	new = ft_malloc_list(sizeof(t_token), ml);
	if (!new)
	{
		perror("allocation failed ");
		//ft_free tout tout
		exit(EXIT_FAILURE);
	}
	new->elem = exp;
	new->token = tmp->token;
	new->next = tmp->next;
	new->prev = tmp->prev;
	//free(tmp->elem); // pas sur
	//ft_free_one_node_ml(tmp, ml); // dutout de ca
	return (new);
}

char	*ft_merge(char *str, char *exp, int i, t_parser *parser, t_mnode **ml)
{
	int		len_before;
	int		len_after;
	char	**tab;
	char	*str_merged;
	
	str_merged = NULL;
	len_before = 0;
	while (i-- != 0)
		len_before++;
	len_after = 0;
	i = parser->end;
	while (i > 0 && str[i++])
		len_after++;
	printf("\tBEFORE : %d \tEXP : %d\t AFTER : %d\n\n", len_before, ft_strlen(exp), len_after);
	str_merged = ft_malloc_list((len_before + ft_strlen(exp) + len_after + 1)
								* sizeof(char), ml);
	if (!str_merged)
		return (NULL); // ou renvoyer l'input sans l'expand ??
	tab = ft_malloc_list(sizeof(char *) * 3, ml);
	if (!tab)
		return (NULL); // je ne sais pas comment gerer | je crois que c'est gerer dans la fonction
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
	if (elem[i] == '$' || elem[i] == '?') // PID du processus en cours
	{
		parser->end = i + 1;
		if (elem[i] == '$')
			return (ft_itoa(getpid())); // PID du processus en cours
		// else
		// 	return (ft_itoa_ml(exit_status)); // dernier exit status
	}
	if (!ft_isalpha(elem[i]) && elem[i] != '_')
		return (NULL);
	while (ft_isalnum(elem[i]) || elem[i] == '_')
		i++;
	parser->end = i;
	var_name = ft_substr_ml(elem, parser->start, i - parser->start, ml);
	if (!var_name)
		return (NULL);
	value_ptr = getenv(var_name); // voir comment gerer les variables d'env car je pense qu'il y a double actuellement
	if (value_ptr)
		var_expanded = ft_strdup_ml(value_ptr, ml);
	else
		var_expanded = ft_strdup_ml("", ml);
	return (var_expanded);
}

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
			ft_inside_quotes_parser(parser, tmp->elem, i);
			if (tmp->elem[i] == '$' && parser->simple_q == OUT_Q
				&& tmp->token != DELIM
				&& (i == 0 || !ft_effect_escape_parser(parser, tmp->elem, i)))
			{
				parser->start = i;
				var_exp = ft_add_brack(ft_expand(tmp->elem, i, parser, ml), ml);
				printf("\n\tExppanded : %s\n\n", var_exp);
				tmp = ft_replace_expanded_elem(ft_merge(tmp->elem, var_exp, i, parser, ml), tmp, ml);
				i = -1;
			}
		}
		printf("\n\n\tELEM_FINAL : %s\n\n", tmp->elem);
		tmp = tmp->next;
	}
}
