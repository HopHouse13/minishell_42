/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/04/09 18:22:56 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_cmds(char *cmd)
{
	printf("\ncmd >> [%s]\n\n", cmd);
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cat") || !ft_strcmp(cmd, "grep")
		|| !ft_strcmp(cmd, "wc") || !ft_strcmp(cmd, "sort")
		|| !ft_strcmp(cmd, "uniq") || !ft_strcmp(cmd, "awk")
		|| !ft_strcmp(cmd, "sed") || !ft_strcmp(cmd, "head")
		|| !ft_strcmp(cmd, "tail"))
		return (true);
	return (false);
}

char	*ft_find_next_cmd(t_parser *parser, t_token *tmp, t_mnode **ml)
{
	while (tmp && tmp->token != END)
	{
		if (tmp->token == CMD)
			return (ft_remove_quotes(parser, tmp->elem, ml));
		tmp = tmp->next;
	}
	return (NULL);
}

// bool	ft_inside_bracket(t_parser *parser, char *str, int i)
// {	
// 	parser->mark_b = false;
// 	if (str[i] == '[')
// 	parser->mark_b = true;
// 	else if (str[i] == ']')
// 	parser->mark_b = false;
// 	return(parser->mark_b);
// }

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
			|| (str[i] != '\'' && str[i] != '\"'))
			count_without_q++;
	str_without_q = ft_malloc_list(sizeof(char) * count_without_q + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if ((ft_inside_quotes_parser(parser, str, i))
			|| (str[i] != '\'' && str[i] != '\"'))
			str_without_q[j++] = str[i];
	str_without_q[j] = '\0';
	return (str_without_q);
}

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet
bool	ft_effect_escape_parser(t_parser *parser, char *str, int i)
{
	bool	on_off;
	
	on_off = false;
	if((parser->double_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
		|| parser->simple_q)
		return (on_off);
	while (--i>= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}