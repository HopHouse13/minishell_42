/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:54:23 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/19 16:53:02 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_init_head_list_ml(void *ptr, size_t size, t_mshell *ms, t_mnode **ml)
{
	t_mnode *first_node;

	first_node = ft_malloc_list(sizeof(t_mnode), ms, ml); // JE CROIS QUE C'EST UN MALLOC SIMPLE A FAIRE ICI
	if (!first_node)
	{
		perror("initialization list ");
		ft_free_ml(ml);
		return;
	}
	first_node->ptr = ptr;
	first_node->size = size;
	first_node->next = NULL;
	*ml = first_node;
}

void ft_add_ml(void *ptr, size_t size, t_mshell *mshell, t_mnode **ml)
{
	t_mnode *new_node;

	if (ml == NULL)
	{
		ft_init_head_list_ml(ptr, size, mshell, ml);
		return;
	}
	new_node = malloc(sizeof(t_mnode));
	if (!new_node)
	{
		free(ptr);
		perror("allocation failed ");
		// ft_free tout tout
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->size = size;
	new_node->next = *ml;
	*ml = new_node;
}

void *ft_malloc_list(size_t size, t_mshell *mshell, t_mnode **ml)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_mem_err();
	ft_add_ml(ptr, size, mshell, ml);
	return (ptr);
}

void *ft_calloc_list(size_t nb, size_t s_type, t_mshell *ms, t_mnode **ml)
{
	void *ptr;

	ptr = ft_calloc(nb, s_type);
	if (!ptr)
		ft_mem_err();
	ft_add_ml(ptr, nb * s_type, ms, ml);
	return (ptr);
}
