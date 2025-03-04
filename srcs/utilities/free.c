/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:46:59 by pbret             #+#    #+#             */
/*   Updated: 2025/03/04 12:55:55 by pbret            ###   ########.fr       */
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
