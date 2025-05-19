/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:09 by pab               #+#    #+#             */
/*   Updated: 2025/05/19 16:57:25 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_open_input(t_mshell *mshell, char *input)
{printf("\n\t-------------------- INPUT_OPEN ---------------------\n");
	int	i;
	
	i = -1;
	while (input[++i])
		ft_status_qts(mshell->qts, input, i);
	if (mshell->qts->spl_q == IN || mshell->qts->dbl_q == IN)
		return (true);
	return (false);
}

void	ft_handle_input(t_mshell *mshell, t_mnode **ml)
{
	char *input_buffer;
	
	if (mshell->input[0] == '\0') //evite de l'ajouter dans l'historique
		return ;
	if (ft_open_input(mshell, mshell->input))
	{
		input_buffer = ft_strdup_ml("\0", mshell, ml);
		while(1)
		{
			input_buffer = ft_strjoin_ml(input_buffer, mshell->input, ml);
			input_buffer = ft_strjoin_ml(input_buffer, "\n", ml);
			if (!ft_open_input(mshell, input_buffer))
				break ;
			free(mshell->input);
			mshell->input = NULL;
			mshell->input = readline("> ");
		}
		mshell->input = ft_strdup_ml(input_buffer, mshell, ml);
	}
	add_history(mshell->input);
}
