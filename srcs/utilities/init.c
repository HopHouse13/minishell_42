/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/05/26 20:31:20 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell **mshell, char **env)
{(void)env; // AAASSSUUUUUUUPPPPPPPP
	*mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		ft_mem_err((*mshell));
	(*mshell)->qts = malloc(sizeof(t_qts));
	if (!(*mshell)->qts)
		ft_mem_err((*mshell));
	(*mshell)->ml = NULL;
	(*mshell)->input = NULL;
	(*mshell)->list_token = NULL;
	(*mshell)->list_cmd = NULL;
	(*mshell)->count_pipe = 0;
	(*mshell)->env_list = NULL;
	// ft_build_env_list(*mshell, env);
	g_exit_code = 0;
}
