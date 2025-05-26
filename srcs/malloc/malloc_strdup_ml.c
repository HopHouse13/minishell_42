/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_strdup_ml.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:10:29 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/26 22:00:20 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_ml(t_mshell *mshell, char *s_src)
{
	char	*s_dup;
	size_t	i;

	s_dup = ft_malloc_list(mshell, sizeof(char) * ft_strlen(s_src) +1);
	if (!s_dup)
		return (NULL);
	i = 0;
	while (s_src[i])
	{
		s_dup[i] = s_src[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
