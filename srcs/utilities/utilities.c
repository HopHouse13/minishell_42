/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:53:07 by pab               #+#    #+#             */
/*   Updated: 2025/05/29 11:31:04 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_empty_line(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_msspace(input[i]))
		i++;
	if (i == ft_strlen(input))
		return (true);
	return (false);
}

int	ft_msspace(char c)
{
	if ((c > 10 && c < 14) || c== 9 || c == 32)
		return (1);
	return (0);
}
