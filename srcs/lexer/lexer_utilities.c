/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/04/01 17:36:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Si c est une quote simple (') et qu'on n'est pas dans une quote double :
// On ouvre ou ferme simple_q.
// marker_q prend OUT_Q.

// Si c est une quote double (") et qu'on n'est pas dans une quote simple :
// On ouvre ou ferme double_q.
// marker_q prend OUT_Q.

// Si simple_q ou double_q est IN_Q alore MARKER_Q prend IN_Q.
// marker_q est retourne.

bool	ft_effect_escape(t_lexer *lexer, char *str, int i)
{
	if (i >= 1 && str[i - 1] == '\\' && !lexer->marker_sq)
	{
		if (i >= 2 && str[i - 2] == '\\')
			return (printf("false\n"), false);
		else
			return (printf("true\n"), true);
	}
	return (printf("false\n"), false);
}

int	ft_inside_quotes_lexer(t_lexer *lexer, char *str, int i)
{
	if (ft_effect_escape(lexer, str, i))
		lexer->marker_q = lexer->marker_q;
	else if (str[i] == '\'' && lexer->double_q == OUT_Q)
	{
		if (lexer->simple_q == IN_Q)
			lexer->simple_q = OUT_Q;
		else 
			lexer->simple_q = IN_Q;
		lexer->marker_q = OUT_Q;
	}
	else if (str[i] == '\"' && lexer->simple_q == OUT_Q)
	{
		if (lexer->double_q == IN_Q)
			lexer->double_q = OUT_Q;
		else
			lexer->double_q = IN_Q;
		lexer->marker_q = OUT_Q;
	}
	else if (lexer->simple_q == IN_Q)
		lexer->marker_sq = IN_Q;
	else if (lexer->double_q == IN_Q)
		lexer->marker_dq = IN_Q;
	if (lexer->marker_sq == IN_Q || lexer->marker_dq == IN_Q)
		lexer->marker_q = IN_Q;
	printf("\tsimple_q: %d\tdouble_q: %d\tmarker_q: %d\tchar: [%c]\n", lexer->simple_q, lexer->double_q, lexer->marker_q, str[i]);
	return (lexer->marker_q);
}

void	ft_init_line(char *virgin_line) // remplir le tab de caracteres de '\0'
{
	int	i;

	i = -1;
	while (++i < SIZE_LINE)
		virgin_line[i] = '\0';
	return ;
}

bool	ft_valid_character(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (false);
	return (true);
}

t_type	ft_builtin_or_cmd(char *elem)
{
	if (!ft_strcmp(elem, "echo") || !ft_strcmp(elem, "cd")
		|| !ft_strcmp(elem, "pwd") || !ft_strcmp(elem, "export")
		|| !ft_strcmp(elem, "unset") || !ft_strcmp(elem, "env")
		|| !ft_strcmp(elem, "exit"))
		return (BI);
	return (CMD);
}