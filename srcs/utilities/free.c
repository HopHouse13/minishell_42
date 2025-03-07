/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:46:59 by pbret             #+#    #+#             */
/*   Updated: 2025/03/05 17:12:48 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_manag(t_mshell *mshell)
{
	int	i;
	
	if (mshell->input)
		free(mshell->input);
	i = -1;
	if (mshell->paths != NULL)
	{
		while (mshell->paths[++i])
			free(mshell->paths[i]);
		free(mshell->paths);
	}
	i = -1;
	if (mshell->env != NULL)
	{
		while (mshell->env[++i])
			free(mshell->env[i]);
		free(mshell->env);
	}
}

void	ft_free_list_token(t_token *list_token)
{
	t_token	*tmp;

	if (!list_token)
		return ;
	while (list_token)
	{
		tmp = list_token;
		list_token = list_token->next;
		free(tmp->elem);
		free(tmp);
	}
	list_token = NULL;
}
