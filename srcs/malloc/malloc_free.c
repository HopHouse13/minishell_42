/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:58:12 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/11 18:07:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_mlist(t_mnode *ml)
{
	t_mnode	*tmp;
 
	while (ml)
	{
		tmp = ml->next;
		free(ml->ptr);
		free(ml);
		tmp = ml;
	}
	ml = NULL;
}