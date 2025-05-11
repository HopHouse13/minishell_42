/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:09 by pab               #+#    #+#             */
/*   Updated: 2025/05/11 20:03:50 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_open_input(t_mshell **mshell, char *input)
{//printf("\n\n\t--------------------INPUT_OPEN--------------------\n");
	int	i;
	
	i = -1;
	while (input[++i])
		ft_status_qts((*mshell)->qts, input, i);
	if ((*mshell)->qts->simple_q == IN || (*mshell)->qts->double_q == IN)
		return (true);
	return (false);
}

void	ft_handle_close_input(t_mshell **mshell, t_mnode **ml)
{
	char *input_buffer;
	
	input_buffer = ft_strdup_ml("\0", ml);
	while(1)
	{
		input_buffer = ft_strjoin_ml(input_buffer, (*mshell)->input, ml);
		input_buffer = ft_strjoin_ml(input_buffer, "\n", ml);
		if (!ft_open_input(mshell, input_buffer))
			break ;
		free((*mshell)->input);
		(*mshell)->input = NULL;
		(*mshell)->input = readline("> ");
	}
	(*mshell)->input = ft_strdup_ml(input_buffer, ml);
}