/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_strjoin_ml.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:31:19 by pab               #+#    #+#             */
/*   Updated: 2025/03/31 15:50:28 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_ml(char const *s1, char const *s2, t_mnode **ml)
{
	size_t	i;
	size_t	j;

	char	*dest;
	dest = ft_malloc_list(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2) +1), ml);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
