/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_elem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:26:59 by pbret             #+#    #+#             */
/*   Updated: 2025/06/03 22:25:25 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_char_saved(t_mshell *mshell, t_parser *parser, char *str, int i)
{
	if (ft_inside_brackets(parser, str, i)
		|| (i >= 2 && str[i -1] == ']' && str[i -2] == '\\'))
		return (true);
	if (str[i] == '\\')
	{
		if (mshell->qts.spl_q)
			return (true);
		if (ft_effect_esc(&mshell->qts, str, i))
			return (true);
		if (mshell->qts.dbl_q)
		{
			if (str[i + 1] == '\\' || str[i + 1] == '$' || str[i + 1] == '\"')
				return (false);
			return (true);
		}
		return (false);
	}
	else if (str[i] == '\'' || str[i] == '\"')
	{
		if (mshell->qts.in_q || ft_effect_esc(&mshell->qts, str, i))
			return (true);
		return (false);
	}
	return (true);
}

// PROBLEME le \ est aussi enleve dans les doubles quotes alors qu'il n'est
//  pas devant " / $
// faut qu'il soit supprimer uniquement devant ces 3 caracteres dans des doubles
char	*ft_remove(t_mshell *mshell, t_parser *parser, char *str)
{
	int		i;
	int		j;
	size_t	count_save;
	char	*str_clear;

	i = -1;
	count_save = 0;
	while (str[++i])
	{
		ft_status_qts(&mshell->qts, str, i);
		if (ft_char_saved(mshell, parser, str, i))
			count_save++;
	}
	str_clear = ft_malloc_list(mshell, sizeof(char) * count_save + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		ft_status_qts(&mshell->qts, str, i);
		if (ft_char_saved(mshell, parser, str, i))
			str_clear[j++] = str[i];
	}
	str_clear[j] = '\0';
	return (str_clear);
}

// on remove les quotes et escape char par tout sauf dans les DELIM
// j'ai besoin d'avoir l'info (expand ou pas dans HD)
// les DELIM seront clear apres avoir stocke l'info lors la crea. de la cmd_list
void	ft_clear_elems(t_mshell *mshell, t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		if (tmp->token != DELIM)
			tmp->elem = ft_remove(mshell, parser, tmp->elem);
		tmp = tmp->next;
	}
}
