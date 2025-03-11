/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:54:23 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/11 22:35:29 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
