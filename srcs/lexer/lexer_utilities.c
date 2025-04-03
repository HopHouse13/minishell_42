/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:53:06 by pbret             #+#    #+#             */
/*   Updated: 2025/04/03 01:05:34 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet
bool	ft_effect_escape(t_lexer *lexer, char *str, int i)
{
	bool	on_off;
	
	on_off = false;
	if((lexer->double_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
		|| lexer->simple_q)
		return (on_off);
	while (--i>= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
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