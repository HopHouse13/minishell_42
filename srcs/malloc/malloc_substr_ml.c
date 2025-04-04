/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_substr_ml.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:27:27 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/04 18:47:44 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_ml(char const *s_src, int start, int len, t_mnode **ml)
{
	char	*s_new;
	int		j;
	
	if (!s_src)
	return (NULL);
	if (start >= ft_strlen(s_src))
	{
		s_new = ft_calloc_list(1, sizeof(char), ml);
		if (!s_new)
			return (NULL);
		return (s_new);
	}
	if (len > ft_strlen(s_src) - start)
	len = ft_strlen(s_src) - start;
	s_new = ft_calloc_list((len + 1), sizeof(char), ml);
	if (!s_new)
		return (NULL);
	j = 0;
	while (j < len && s_src[start] != '\0')
		printf("test4\n"), s_new[j++] = s_src[start++];
	s_new[j] = '\0';
	return (s_new);
}
