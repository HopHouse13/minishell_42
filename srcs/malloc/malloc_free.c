/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:58:12 by ubuntu            #+#    #+#             */
/*   Updated: 2025/05/27 16:43:54 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_env(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
	env_list = NULL;
}

void	ft_free_ml(t_mshell *mshell)
{
	t_mnode	*tmp;

	if (!mshell->ml)
		return ;
	while (mshell->ml)
	{
		tmp = mshell->ml->next;
		free(mshell->ml->ptr);
		free(mshell->ml);
		mshell->ml = tmp;
	}
	free(mshell->ml);
	mshell->ml = NULL;
}

void	ft_free_one_node_ml(void *ptr, t_mnode **ml)
{
	t_mnode	*tmp;
	t_mnode	*prev;

	if (!ml)
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
		tmp = tmp->next;
	}
}
