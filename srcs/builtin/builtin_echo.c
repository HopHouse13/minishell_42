/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:07:23 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 19:13:54 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_args(char **tab_args)
{
	int	count;

	count = 0;
	while (tab_args[count])
		count++;
	return (count);
}

bool	ft_valid_option_n(char *arg)
{
	int	i;

	i = -1;
	if (arg[++i] != '-')
		return (false);
	while (arg[++i])
	{
		if(arg[i] != 'n')
			return (false);
	}
	return (true);
}

int	ft_echo(t_mshell *mshell)
{
	int		i;
	bool	option;
	int		args_count;
	char	**cmd;

	cmd = mshell->list_cmd->cmd;
	args_count = ft_count_args(cmd) -1;
	option = false;
	i = 0;
	while (++i < args_count)
	{
		if (ft_valid_option_n(cmd[i]))
		{
			option = true;
			continue ;
		}
		else
			break ;
	}
	while (i < args_count)
		printf("%s ", cmd[i++]);
	printf("%s", cmd[i]);
	if (!option)
		printf("\n");
	return (0);
}
