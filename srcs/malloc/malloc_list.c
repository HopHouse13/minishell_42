/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:54:23 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/11 22:02:24 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_ml(char const *s_src, int start, int len, t_mnode ml)
{
	char	*s_new;
	int		j;

	if (!s_src)
		return (NULL);
	if (start >= ft_strlen(s_src))
	{
		s_new = ft_calloc(1, sizeof(char));
		if (!s_new)
			return (NULL);
		return (s_new);
	}
	if (len > ft_strlen(s_src) - start)
		len = ft_strlen(s_src) - start;
	s_new = ft_calloc((len + 1), sizeof(char));
	if (!s_new)
		return (NULL);
	j = 0;
	while (j < len && s_src[start])
		s_new[j++] = s_src[start++];
	s_new[j] = '\0';
	return (s_new);
}

void	ft_add_ml(void *ptr, size_t size, t_mnode *ml)
{
	t_mnode *new_node;

	new_node = malloc(sizeof(t_mnode));
	if (!new_node)
	{
		free(ptr);
		perror("allocation failed ");
		//ft_free tout tout
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->size = size;
	new_node->next = ml;
	ml = new_node;
		
}

void	*ft_malloc_list(size_t size, t_mnode *ml)
{
	void	*ptr;
	
	ptr = NULL;
	ptr = malloc(size);
	if (!size)
	{
		perror("allocation failed ");
		//ft_free tout tout
		exit(EXIT_FAILURE);
	}
	ft_add_ml(ptr, size, ml);
	return (ptr);
}

void	*ft_calloc_list(size_t nb, size_t size_type, t_mnode *ml)
{
	void	*ptr;
	
	ptr = NULL;
	ptr = ft_calloc(nb, size_type);
	if (!ptr)
	{
		perror("allocation failed ");
		//ft_free tout tout
		exit(EXIT_FAILURE);
	}
	ft_add_ml(ptr, nb * size_type, ml);
	return (ptr);
}
