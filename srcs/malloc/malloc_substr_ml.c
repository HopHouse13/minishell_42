/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_substr_ml.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:27:27 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/26 22:00:09 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_ml(t_mshell *mshell, char *s_src, int start, int len)
{
	char	*s_new;
	int		j;

	if (!s_src)
		return (NULL);
	if (start >= ft_strlen(s_src))
	{
		s_new = ft_calloc_list(mshell, 1, sizeof(char));
		if (!s_new)
			return (NULL);
		return (s_new);
	}
	if (len > ft_strlen(s_src) - start)
		len = ft_strlen(s_src) - start;
	s_new = ft_calloc_list(mshell, (len + 1), sizeof(char));
	if (!s_new)
		return (NULL);
	j = 0;
	while (j < len && s_src[start] != '\0')
		s_new[j++] = s_src[start++];
	s_new[j] = '\0';
	return (s_new);
}
