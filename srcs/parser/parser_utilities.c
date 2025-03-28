/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:32:42 by pab               #+#    #+#             */
/*   Updated: 2025/03/28 11:17:18 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_cmds(char *cmd)
{
	printf(">> [%s]\n\n", cmd);
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
	printf("carac copie -> %ld\n", count_without_q + 1);
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
// On ouvre ou ferme simpleq.
// On retourne OUT_Q.

// Si c est une quote double (") et qu'on n'est pas dans une quote simple :
// On ouvre ou ferme doubleq.
// On retourne OUT_Q.

// On retourne 1 si on est dans une quote (simpleq ou doubleq), sinon 0.
int	ft_inside_quotes_parser(t_parser *parser, char c)
{
	if (c == '\'' && parser->doubleq == OUT_Q)
	{
		if (parser->simpleq == IN_Q)
			parser->simpleq = OUT_Q;
		else 
			parser->simpleq = IN_Q;
		return (OUT_Q);
	}
	if (c == '\"' && parser->simpleq == OUT_Q)
	{
		if (parser->doubleq == IN_Q)
			parser->doubleq = OUT_Q;
		else
			parser->doubleq = IN_Q;
		return (OUT_Q);
	}
	printf("S_quote: %d\tD_quote: %d\n", parser->simpleq, parser->doubleq);
	return (parser->simpleq == IN_Q || parser->doubleq == IN_Q);
}
/* int	ft_inside_quotes_parser(t_parser *parser, char c)
{
	if (c == '\'' && parser->doubleq == OUT_Q && parser->simpleq == OUT_Q)
		parser->simpleq = IN_Q;
	else if (c == '\'' && parser->simpleq == IN_Q && parser->doubleq == OUT_Q)
		parser->simpleq = OUT_Q;
	else if (c == '\'' && parser->simpleq == OUT_Q && parser->doubleq == IN_Q)
		parser->doubleq = IN_Q;
	else if (c == '\"' && parser->simpleq == OUT_Q && parser->doubleq == OUT_Q)
		parser->doubleq = IN_Q;
	else if (c == '\"' && parser->doubleq == IN_Q && parser->simpleq == OUT_Q)
		parser->doubleq = OUT_Q;
	else if (c == '\"' && parser->simpleq == IN_Q && parser->doubleq == OUT_Q)
		parser->simpleq = IN_Q;
	if ((parser->simpleq == IN_Q || parser->doubleq == IN_Q) 
		&& (c != '\'' && c != '\"'))
		parser->flag_q = IN_Q;
	else
		parser->flag_q = OUT_Q;
	printf("S_quote : %d\tD_quote : %d\t>>> value quotes : %d\n",parser->simpleq, parser->doubleq, parser->flag_q);
	return (parser->flag_q);
} */
