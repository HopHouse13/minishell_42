/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/05/08 19:42:57 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell *mshell, char **env)
{
	mshell->input = NULL;
	mshell->list_token = NULL;
	mshell->list_cmd = NULL;
	mshell->count_pipe = 0;
	mshell->exit_status = 0;
	mshell->env_list = NULL;
	ft_build_env_list(mshell, env);
	exit_code = 0;
}
