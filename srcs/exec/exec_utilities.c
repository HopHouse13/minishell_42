/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:59:48 by pab               #+#    #+#             */
/*   Updated: 2025/05/12 19:17:51 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_effect_escape_hd(char *str, int i)
{
	bool	on_off;

	on_off = false;
	while (--i >= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}

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
	if (line[i] == '\\' && !ft_effect_escape_hd(line, i))
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

int	ft_check_path_access(char *cmd)
{
	if (access(cmd, F_OK) == -1) // + X_OK pour verif droit d'execution
		exit(127); // commande not found
	if (access(cmd, X_OK) == -1)
		exit(126); // pas executable
	return (1);
}