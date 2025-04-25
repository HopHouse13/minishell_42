/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:59:48 by pab               #+#    #+#             */
/*   Updated: 2025/04/25 01:42:52 by pab              ###   ########.fr       */
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
