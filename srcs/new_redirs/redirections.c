/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:24:49 by phautena          #+#    #+#             */
/*   Updated: 2025/06/19 16:16:22 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*next_pipe(t_token *token, t_cmd *cmd)
{
	if (!cmd->next)
		return (token);
	while (token->token != PIPE)
		token = token->next;
	token = token->next;
	return (token);
}

static t_token	*next_token(t_token *token)
{
	while (token->token != R_IN && token->token != R_OUT
		&& token->token != APPEND && token->token != HD)
		token = token->next;
	return (token);
}

static int	count_redirs(t_token *token)
{
	t_token	*temp;
	int		count;

	temp = token;
	count = 0;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == R_IN || temp->token == R_OUT
			|| temp->token == APPEND || temp->token == HD)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	set_files(t_cmd *cmd, t_token *token, t_mshell *mshell, t_parser *parser)
{
	if (!ft_strcmp(token->elem, "<"))
	{
		if (set_infile(cmd, token->next))
			return (1);
	}
	else if (!ft_strcmp(token->elem, "<<"))
	{
		if (set_hd(cmd, token, mshell, parser))
			return (1);
	}
	else if (!ft_strcmp(token->elem, ">"))
	{
		if (set_outfile(cmd, token, 1))
			return (1);
	}
	else
	{
		if (set_outfile(cmd, token, 0))
			return (1);
	}
	return (0);
}

void	init_redirections(t_mshell *mshell, t_parser *parser)
{
	t_cmd	*cmd;
	t_token	*token;
	int		count;

	cmd = parser->list_cmd;
	token = mshell->list_token;
	while (cmd)
	{
		count = count_redirs(token);
		while (count-- > 0)
		{
			token = next_token(token);
			if (set_files(cmd, token, mshell, parser))
			{
				cmd->no_cmd = true;
				g_exit_code = 1;
				break ;
			}
			token = token->next;
		}
		token = next_pipe(token, cmd);
		cmd = cmd->next;
	}
}
