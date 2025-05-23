/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:09 by pab               #+#    #+#             */
/*   Updated: 2025/05/21 17:19:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_open_input(t_mshell *mshell, char *input)
{printf("\n\t-------------------- INPUT_OPEN ---------------------\n");
	int	i;
	
	i = -1;
	while (input[++i])
		ft_status_qts(mshell->qts, input, i);
	if (mshell->qts->spl_q || mshell->qts->dbl_q)
		return (true);
	return (false);
}

void	ft_handle_input(t_mshell *mshell)
{
	char *input_buff;
	
	if (mshell->input[0] == '\0') //evite de l'ajouter dans l'historique
		return ;
	if (ft_open_input(mshell, mshell->input))
	{
		input_buff = ft_strdup_ml(mshell, "\0");
		while(1)
		{
			input_buff = ft_strjoin_ml(mshell, input_buff, mshell->input);
			input_buff = ft_strjoin_ml(mshell, input_buff, "\n");
			if (!ft_open_input(mshell, input_buff))
				break ;
			free(mshell->input);
			mshell->input = NULL;
			mshell->input = readline("> ");
		}
		mshell->input = ft_strdup_ml(mshell, input_buff);
	}
	add_history(mshell->input);
}
