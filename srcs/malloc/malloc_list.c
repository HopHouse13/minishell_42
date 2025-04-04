/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:54:23 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/04 18:47:36 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_head_list_ml(void *ptr, size_t size, t_mnode **ml)
{
	t_mnode *first_node;

	first_node = ft_malloc_list(sizeof(t_mnode), ml);
	if (!first_node)
	{
		perror("initialization list ");
		ft_free_ml(ml);
		return ;
	}
	first_node->ptr = ptr;
	first_node->size = size;
	first_node->next = NULL;
	*ml = first_node;
}

void	ft_add_ml(void *ptr, size_t size, t_mnode **ml)
{
	t_mnode *new_node;
	if (ml == NULL)
	{
		ft_init_head_list_ml(ptr, size, ml);
		return ;
	}
	printf("TEST\n");
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
	new_node->next = *ml;
	*ml = new_node;	
}

void	*ft_malloc_list(size_t size, t_mnode **ml)
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

void	*ft_calloc_list(size_t nb, size_t size_type, t_mnode **ml)
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
	printf("value_ptr : %p\n", ptr);
	return (ptr);
}


