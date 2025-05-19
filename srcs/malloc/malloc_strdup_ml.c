/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_strdup_ml.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:10:29 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/19 16:53:41 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_ml(const char *s_src, t_mshell *mshell, t_mnode **ml)
{
	char	*s_dup;
	size_t	i;

	s_dup = ft_malloc_list(sizeof(char) * ft_strlen(s_src) +1, mshell, ml);
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