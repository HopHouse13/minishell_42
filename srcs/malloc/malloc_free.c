/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:58:12 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/12 18:31:09 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_ml(t_mnode **ml)
{
	t_mnode	*tmp;

	if (ml == NULL || *ml == NULL)
		return ;
	while (*ml)
	{
		tmp = (*ml)->next;
		free((*ml)->ptr);
		free(*ml);
		*ml = tmp;
	}
	*ml = NULL;
	ml = NULL; // utilse ???
}

void	ft_free_one_node_ml(void *ptr, t_mnode **ml)
{
	t_mnode	*tmp;
	t_mnode	*prev;
	
	if (ml == NULL)
		return ;
	tmp = *ml;
	prev = NULL;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*ml = tmp->next;
			free(tmp->ptr);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->	next;
	}
}
