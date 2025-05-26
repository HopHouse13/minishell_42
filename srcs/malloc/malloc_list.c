/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:54:23 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/26 22:03:04 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_head_list_ml(t_mshell *mshell, void *ptr, size_t size)
{
	t_mnode	*first_node;

	first_node = malloc(sizeof(t_mnode));
	if (!first_node)
		ft_mem_err(mshell);
	first_node->ptr = ptr;
	first_node->size = size;
	first_node->next = NULL;
	mshell->ml = first_node;
}

void	ft_add_ml(t_mshell *mshell, void *ptr, size_t size)
{
	t_mnode	*new_node;

	if (mshell->ml == NULL)
		ft_init_head_list_ml(mshell, ptr, size);
	else
	{
		new_node = malloc(sizeof(t_mnode));
		if (!new_node)
			ft_mem_err(mshell);
		new_node->ptr = ptr;
		new_node->size = size;
		new_node->next = mshell->ml;
		mshell->ml = new_node;
	}
}

void	*ft_malloc_list(t_mshell *mshell, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_mem_err(mshell);
	ft_add_ml(mshell, ptr, size);
	return (ptr);
}

void	*ft_calloc_list(t_mshell *mshell, size_t nb, size_t size_type)
{
	void	*ptr;

	ptr = ft_calloc(nb, size_type);
	if (!ptr)
		ft_mem_err(mshell);
	ft_add_ml(mshell, ptr, nb * size_type);
	return (ptr);
}
