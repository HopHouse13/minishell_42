/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:53:07 by pab               #+#    #+#             */
/*   Updated: 2025/05/09 17:20:05 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_empty_line(char *input)
{
	int	i;
	
	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (i == ft_strlen(input))
		return (true);
	return (false);
}