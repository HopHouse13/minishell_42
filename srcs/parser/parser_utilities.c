/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/04/02 12:48:24 by pbret            ###   ########.fr       */
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

char	*ft_remove_quotes(t_parser *parser, char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_without_q;
	char	*str_without_q;
	
	i = -1;
	count_without_q = 0;
	while (str[++i])
		if (ft_inside_quotes_parser(parser, str[i])
			|| (str[i] != '\'' && str[i] != '\"'))
			count_without_q++;
	str_without_q = ft_malloc_list(sizeof(char) * count_without_q + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if ((ft_inside_quotes_parser(parser, str[i]))
			|| (str[i] != '\'' && str[i] != '\"'))
			str_without_q[j++] = str[i];
	str_without_q[j] = '\0';
	return (str_without_q);
}

// Si c est une quote simple (') et qu'on n'est pas dans une quote double :
// On ouvre ou ferme simple_q.
// mark_q prend OUT_Q.

// Si c est une quote double (") et qu'on n'est pas dans une quote simple :
// On ouvre ou ferme double_q.
// mark_q prend OUT_Q.

// Si simple_q ou double_q est IN_Q alore mark_Q prend IN_Q.
// mark_q est retourne.
int	ft_inside_quotes_parser(t_parser *parser, char c)
{
	if (c == '\'' && parser->double_q == OUT_Q)
	{
		if (parser->simple_q == IN_Q)
			parser->simple_q = OUT_Q;
		else 
			parser->simple_q = IN_Q;
		parser->mark_q = OUT_Q;
	}
	else if (c == '\"' && parser->simple_q == OUT_Q)
	{
		if (parser->double_q == IN_Q)
			parser->double_q = OUT_Q;
		else
			parser->double_q = IN_Q;
		parser->mark_q = OUT_Q;
	}
	else if (parser->simple_q == IN_Q || parser->double_q == IN_Q)
		parser->mark_q = IN_Q;
	printf("\tsimple_q: %d\tdouble_q: %d\t\tmark_q: %d\n", parser->simple_q, parser->double_q, parser->mark_q);
	return (parser->mark_q);
}
