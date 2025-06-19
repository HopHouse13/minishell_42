/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:00:09 by pab               #+#    #+#             */
/*   Updated: 2025/06/19 16:31:27 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_pipe_last(t_mshell *mshell, char *input)
{
	int		i;
	bool	pipe;

	i = -1;
	pipe = false;
	while (input[++i])
	{
		if ((!ft_status_qts(&mshell->qts, input, i)
				|| ft_effect_esc(&mshell->qts, input, i))
			&& input[i] == '|')
			pipe = true;
		else if (!ft_msspace(input[i]))
			pipe = false;
	}
	return (pipe);
}

bool	ft_open_quotes(t_mshell *mshell, char *input)
{
	int		i;
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	i = -1;
	while (input[++i])
	{
		if (!ft_status_qts(&mshell->qts, input, i)
			&& !ft_effect_esc(&mshell->qts, input, i))
		{
			if (input[i] == '\'')
				sq = !sq;
			else if (input[i] == '\"')
				dq = !dq;
		}
	}
	if (sq || dq)
		return (true);
	return (false);
}

bool	ft_incomplete_cmd(t_mshell *mshell, char *input)
{
	if (!ft_open_quotes(mshell, input) && !ft_pipe_last(mshell, input))
		return (false);
	return (true);
}

void	ft_handle_input(t_mshell *mshell)
{
	char	*input_buff;

	if (mshell->input[0] == '\0')
		return ;
	if (ft_incomplete_cmd(mshell, mshell->input))
	{
		input_buff = ft_strdup_ml(mshell, "\0");
		while (1)
		{
			input_buff = ft_strjoin_ml(mshell, input_buff, mshell->input);
			if (!ft_incomplete_cmd(mshell, input_buff))
				break ;
			if (!ft_pipe_last(mshell, input_buff))
				input_buff = ft_strjoin_ml(mshell, input_buff, "\n");
			free(mshell->input);
			mshell->input = NULL;
			mshell->input = readline("> ");
		}
		mshell->input = ft_strdup_ml(mshell, input_buff);
	}
	add_history(mshell->input);
}
