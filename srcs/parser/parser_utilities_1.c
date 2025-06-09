/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:46:06 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 20:46:26 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_found_dollar_active(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !ft_effect_escape_hd(str, i))
			return (true);
	}
	return (false);
}

bool	ft_escape_last_char(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		continue;
	i--;
	if (i > 0 && line[i] == '\\' && !ft_effect_escape_hd(line, i))
		return (true);
	return (false);
}

int ft_ispath(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
