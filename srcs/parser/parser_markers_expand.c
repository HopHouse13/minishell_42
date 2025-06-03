/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_markers_expand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:25 by pbret             #+#    #+#             */
/*   Updated: 2025/06/03 16:17:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_find_end_var(char *str, int i)
{
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i + 2); // pour me mettre juste apres le carac invalide
	while (ft_isalnum(str[i]) || str[i] == '_') // ici on arrive deja la bonne position just +1 pour passe d'un adexe a un eme positionemment (bcp de mal avec ca)
		i++;
	return (i + 1);
}

char	*ft_insert_marker(t_mshell *mshell, char *str, int i)
{
	char	*result;
	int		j;
	int		k;
	int		end_name;
	
	end_name = 0;
	end_name = ft_find_end_var(str, i);
	printf("\tvalue end : %d\n\n", end_name);
	result = ft_calloc_list(mshell, ft_strlen(str) + 3, sizeof(char));
	j = 0;
	k = 0;
	while (str[j])
	{
		if (k == i)
			result[k++] = '[';
		result[k++] = str[j++];
		if (k == end_name)
			result[k++] = ']';
	}
	printf("\n\tresult_marker : %s\n\n", result);
	return (result);
}

char	*ft_marker(t_mshell *mshell, t_token *tmp, t_parser *parser)
{
	int		i;
	char	*str;
	
	str = tmp->elem;
	i = -1;
	while (str[++i])
	{
		ft_status_qts(&mshell->qts, str, i);
		if (str[i] == '$'
			&& mshell->qts.spl_q == OUT
			&& tmp->token != DELIM
			&& (i == 0 || !ft_effect_esc(&mshell->qts, str, i))
			&& !ft_inside_brackets(parser, str, i))
		{
			str = ft_insert_marker(mshell, str, ++i);
			i++;
		}
	}
	return (str);	
}

void	ft_mark_expand(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_marker(mshell, tmp, parser);
		tmp = tmp->next;
	}
}
