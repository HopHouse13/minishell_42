/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/05/28 13:37:13 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell **mshell, char **env)
{
	*mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		ft_mem_err((*mshell));
	(*mshell)->input = NULL;
	(*mshell)->list_token = NULL;
	(*mshell)->list_cmd = NULL;
	(*mshell)->env_list = NULL;
	(*mshell)->ml = NULL;
	(*mshell)->count_pipe = 0;
	(*mshell)->shlvl = 0;
	(*mshell)->pwd = NULL;
	ft_build_env_list(*mshell, env);
	g_exit_code = 0;
}
