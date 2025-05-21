/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/05/21 16:55:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell **mshell/* , char **env */)
{
	*mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return ; //ft_error_exit("Error main "); // mauvaise fonction, a faire
	(*mshell)->qts = malloc(sizeof(t_qts));
	if (!(*mshell)->qts)
		return ;
	// (*mshell)->ml = malloc(sizeof(t_mnode *));
	// if (!(*mshell)->ml)
	// 	return ;
	// *(*mshell)->ml = NULL;
	(*mshell)->ml = NULL;
	(*mshell)->input = NULL;
	(*mshell)->list_token = NULL;
	(*mshell)->list_cmd = NULL;
	(*mshell)->count_pipe = 0;
	(*mshell)->env_list = NULL;
	// ft_build_env_list(*mshell, env);
	g_exit_code = 0;
}
