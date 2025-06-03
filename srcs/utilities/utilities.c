/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:53:07 by pab               #+#    #+#             */
/*   Updated: 2025/06/03 20:50:41 by pbret            ###   ########.fr       */
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
	if ((c > 10 && c < 14) || c == 9 || c == 32)
		return (1);
	return (0);
}
