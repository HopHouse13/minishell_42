/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:09 by pab               #+#    #+#             */
/*   Updated: 2025/05/26 20:37:56 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_open_input(t_mshell *mshell, char *input)
{
	int	i;

	printf("\n\t-------------------- INPUT_OPEN ---------------------\n");
	i = -1;
	while (input[++i])
		ft_status_qts(mshell->qts, input, i);
	if (mshell->qts->spl_q || mshell->qts->dbl_q)
		return (true);
	return (false);
}

void	ft_handle_input(t_mshell *mshell)
{
	char	*input_buff;

	if (mshell->input[0] == '\0')
		return ;
	if (ft_open_input(mshell, mshell->input))
	{
		input_buff = ft_strdup_ml(mshell, "\0");
		while (1)
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
