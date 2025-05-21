/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_strjoin_ml.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:31:19 by pab               #+#    #+#             */
/*   Updated: 2025/05/21 17:29:15 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_ml(t_mshell *mshell, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	int		total_len;
	char	*dest;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_malloc_list(mshell, sizeof(char) * (total_len +1));
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
