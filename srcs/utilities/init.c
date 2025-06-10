/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/06/10 17:25:40 by phautena         ###   ########.fr       */
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
	(*mshell)->envp = env;
	ft_build_env_list(*mshell, env);
	g_exit_code = 0;
}
